/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <jpeyron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:58:10 by jpeyron           #+#    #+#             */
/*   Updated: 2021/10/27 17:26:18 by jpeyron          ###   ########.fr       */
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
		if (gettimeofday(&philo->humans[i].last_meal, NULL))
			return (0);
		philo->humans[i].meals = -1;
		if (philo->must_eat_nb != -1)
			philo->humans[i].meals = philo->must_eat_nb;
		pthread_mutex_init(&philo->humans[i].fork_mutex, NULL);
	}
	return (1);
}

void	*philo_routine(void *arg)
{
	t_human	*human;
	t_philo	*philo;
	int		error;

	human = (t_human *)arg;
	philo = human->philo;
	error = 0;
	if (human->name % 2 == 0)
	{
		if (usleep(100) == -1)
			return (NULL);
	}
	while (!human->stop)
	{
		if (!error && !take_forks(human, philo->humans))
			error = 1;
		if (!error && !start_eating(human, philo))
			error = 1;
		if (!error && !drop_forks(human, philo->humans))
			error = 1;
		if (!error && !start_sleeping(human, philo))
			error = 1;
		if (error == 1)
			break ;
		print_status(human->name, "is thinking", philo);
	}
	init_ret_error(philo, error);
	return (NULL);
}

void	stop_threads(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->nb_philo)
		philo->humans[i].stop = 1;
}

int		watch_philosophers(t_philo *philo)
{
	t_human	human;
	int		i;

	i = -1;
	while (++i < philo->nb_philo)
	{
		human = philo->humans[i];
		if (human.meals == 0)
			human.stop = 1;
		
	}
}

void	*philo_watcher(void *arg)
{
	t_philo	*philo;
	int		i;
	int		error;

	philo = (t_philo *)arg;
	error = 0;
	while (1)
	{
		error = watch_philosophers(philo);
		if (error)
	}
	return (NULL);
}

int	start_philos(t_philo *philo)
{
	int	i;
	int	error;

	i = -1;
	error = 0;
	if (gettimeofday(&philo->started, NULL))
		return (-1);
	while (++i < philo->nb_philo)
	{
		if (pthread_create(&philo->humans[i].thread, NULL, philo_routine,
			&philo->humans[i]))
			return (-1);
	}
	if (pthread_create(&philo->thread, NULL, philo_watcher, philo))
		return (-1);
	while (i-- > 0)
		pthread_join(philo->humans[i].thread, NULL);
	pthread_join(philo->thread, NULL);
	return (1);
}