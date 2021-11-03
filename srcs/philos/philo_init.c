/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <jpeyron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:58:10 by jpeyron           #+#    #+#             */
/*   Updated: 2021/11/03 18:11:37 by jpeyron          ###   ########.fr       */
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
		gettimeofday(&philo->humans[i].last_meal, NULL);
		philo->humans[i].meals = -1;
		philo->humans[i].right_ph = philo->humans[i].name;
		if (philo->must_eat_nb != -1)
			philo->humans[i].meals = philo->must_eat_nb;
		if (philo->humans[i].name == philo->nb_philo)
			philo->humans[i].right_ph = 0;
		pthread_mutex_init(&philo->humans[i].fork_mutex, NULL);
		pthread_mutex_init(&philo->humans[i].meal_mutex, NULL);
		pthread_mutex_init(&philo->humans[i].stop_mutex, NULL);
	}
	return (1);
}

void	*philo_routine(void *arg)
{
	t_human	*human;
	t_philo	*philo;

	human = (t_human *)arg;
	philo = human->philo;
	if (human->name % 2 == 0)
	{
		if (usleep(100) == -1)
			return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&human->stop_mutex);
		if (human->stop)
			break ;
		pthread_mutex_unlock(&human->stop_mutex);
		take_forks(human, philo->humans);
		start_eating(human, philo);
		drop_forks(human, philo->humans);
		start_sleeping(human, philo);
		print_status(human->name, "is thinking", philo);
	}
	pthread_mutex_unlock(&human->stop_mutex);
	return (NULL);
}

void	stop_threads(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->nb_philo)
	{
		pthread_mutex_lock(&philo->humans[i].stop_mutex);
		philo->humans[i].stop = 1;
		pthread_mutex_unlock(&philo->humans[i].stop_mutex);
	}
}

int		watch_philosophers(t_philo *philo)
{
	t_human	human;
	int		i;
	int		br;

	i = -1;
	br = 0;
	while (++i < philo->nb_philo)
	{
		human = philo->humans[i];
		pthread_mutex_lock(&human.stop_mutex);
		if (human.stop != 1)
		{
			pthread_mutex_unlock(&human.stop_mutex);
			pthread_mutex_lock(&human.meal_mutex);
			if (millis_time_since(human.last_meal) > philo->die_time)
			{
				pthread_mutex_unlock(&human.meal_mutex);
				print_status(human.name, "died", philo);
				return (1);
			}
			pthread_mutex_unlock(&human.meal_mutex);
		}
		else
		{
			br++;
			pthread_mutex_unlock(&human.stop_mutex);
		}
	}
	if (br == philo->nb_philo)
		return (2);
	else
		return (0);
}

void	*philo_watcher(void *arg)
{
	t_philo	*philo;
	int		error;

	philo = (t_philo *)arg;
	error = 0;
	while (1)
	{
		error = watch_philosophers(philo);
		if (error)
			break ;
		usleep(100);
	}
	if (error != 2)
		stop_threads(philo);
	return (NULL);
}

int	start_philos(t_philo *philo)
{
	int	i;

	i = -1;
	gettimeofday(&philo->started, NULL);
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