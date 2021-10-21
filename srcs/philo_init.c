/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <jpeyron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:58:10 by jpeyron           #+#    #+#             */
/*   Updated: 2021/10/21 18:26:53 by jpeyron          ###   ########.fr       */
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
	}
	return (1);
}

void	*philo_routine(void *arg)
{
	t_human	*human;

	human = (t_human *)arg;
	return (NULL);
}

int	check_at_philos(t_philo *philo)
{
	(void)philo;
	return (1);
}

int	start_philos(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->nb_philo)
	{
		if (pthread_create(philo->humans[i].thread, NULL, philo_routine,
			&philo->humans[i]) || gettimeofday(&philo->humans[i].started, NULL))
			return (-1);
	}
	return (check_at_philos(philo));
}