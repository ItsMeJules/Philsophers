/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:35:07 by jules             #+#    #+#             */
/*   Updated: 2021/11/14 20:23:41 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		philo_live(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->fork_mutex);
	print_status(philo->name, "has taken a fork", data);
	pthread_mutex_lock(&data->philos[philo->next_fork].fork_mutex);
	print_status(philo->name, "has taken a fork", data);
	pthread_mutex_lock(&philo->meal_mutex);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo->name, "is eating", data);
	better_sleep(data->tte, philo);
	if (should_stop(data))
	{
		pthread_mutex_unlock(&data->philos[philo->next_fork].fork_mutex);
		pthread_mutex_unlock(&philo->fork_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->philos[philo->next_fork].fork_mutex);
	pthread_mutex_unlock(&philo->fork_mutex);
	print_status(philo->name, "is sleeping", data);
	better_sleep(data->tts, philo);
	if (should_stop(data))
		return (1);
	print_status(philo->name, "is thinking", data);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->meals > 0 || philo->meals == -1)
	{
		if (philo->data->nb_philo == 1)
		{
			print_status(philo->name, "has taken a fork", philo->data);
			better_sleep(philo->data->ttd, philo);
			return (NULL);
		}
		if (should_stop(philo->data))
			return (NULL);
		if (philo_live(philo, philo->data))
			return (NULL);
		if (philo->meals != -1)
			philo->meals--;
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->data->finished++;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (NULL);
}

void	*philo_watcher(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	int		i;

	data = (t_data *)arg;
	while (42)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			philo = &data->philos[i];
			if (should_stop(data))
				return (NULL);
			pthread_mutex_lock(&philo->meal_mutex);
			if (millis_time_since(philo->last_meal) > data->ttd)
			{
				print_status(philo->name, "died", data);
				pthread_mutex_lock(&data->stop_mutex);
				data->stop = 1;
				pthread_mutex_unlock(&data->stop_mutex);
				pthread_mutex_unlock(&philo->meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->meal_mutex);
		}
		usleep(100);
	}
	return (NULL);
}

void	start_threads(t_philo *philos, int nb_philo, int index)
{
	while (index < nb_philo)
	{
		pthread_create(&philos[index].thread, NULL, philo_routine, &philos[index]);
		index += 2;
	}
}

void	start_simulation(t_data *data)
{
	int	i;

	gettimeofday(&data->started, NULL);
	start_threads(data->philos, data->nb_philo, 1);
	usleep(50);
	start_threads(data->philos, data->nb_philo, 0);
	pthread_create(&data->thread, NULL, philo_watcher, data);
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(data->thread, NULL);
}