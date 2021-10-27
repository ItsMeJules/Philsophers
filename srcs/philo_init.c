/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <jpeyron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:58:10 by jpeyron           #+#    #+#             */
/*   Updated: 2021/10/27 13:02:48 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_philo *philo)
{
	int	i;

	i = -1;
	philo->humans = malloc(philo->nb_philo * sizeof(t_human));
	if (!philo->humans)
		return (0);
	memset(philo->humans, 0, philo->nb_philo * sizeof(t_human));
	while (++i < philo->nb_philo)
	{
		philo->humans[i].name = i + 1;
		philo->humans[i].philo = philo;
		pthread_mutex_init(&philo->humans[i].fork_mutex, NULL);
	}
	return (1);
}

void	*philo_routine(void *arg)
{
	t_human	*human;

	human = (t_human *)arg;
	if (human->name % 2 == 0)
	{
		if (usleep(50) == -1)
			return (NULL);
	}
	if (!take_forks(human, human->philo->humans))
		return (NULL);
	if (!start_eating(human))
		return (NULL);
	if (!drop_forks(human, human->philo->humans))
		return (NULL);
	// if (!start_sleeping(human))
	// 	return (NULL);
	return (NULL);
}

int	check_at_philos(t_philo *philo)
{
	int	i;
	
	i = -1;
	while (++i < philo->nb_philo)
		pthread_join(philo->humans[i].thread, NULL);
	return (1);
}

int	start_philos(t_philo *philo)
{
	int	i;

	i = -1;
	if (gettimeofday(&philo->started, NULL))
		return (-1);
	while (++i < philo->nb_philo)
	{
		if (pthread_create(&philo->humans[i].thread, NULL, philo_routine,
			&philo->humans[i]))
			return (-1);
	}
	return (check_at_philos(philo));
}