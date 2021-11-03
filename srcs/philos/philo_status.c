/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <jpeyron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:43:47 by jpeyron           #+#    #+#             */
/*   Updated: 2021/11/03 17:22:00 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(int name, char *msg, t_philo *philo)
{
	long	time;

	time = millis_time_since(philo->started);
	pthread_mutex_lock(&philo->print_mutex);
	printf("%ldms %d %s\n", time, name, msg);
	pthread_mutex_unlock(&philo->print_mutex);
}

void	take_forks(t_human *human, t_human *h_tab)
{
	pthread_mutex_lock(&human->fork_mutex);
	print_status(human->name, "has taken a fork", human->philo);
	pthread_mutex_lock(&h_tab[human->right_ph].fork_mutex);
	print_status(human->name, "has taken a fork", human->philo);
}

void	drop_forks(t_human *human, t_human *h_tab)
{
	pthread_mutex_unlock(&human->fork_mutex);
	pthread_mutex_unlock(&h_tab[human->right_ph].fork_mutex);
}

void	start_eating(t_human *human, t_philo *philo)
{
	pthread_mutex_lock(&human->meal_mutex);
	gettimeofday(&human->last_meal, NULL);
	pthread_mutex_unlock(&human->meal_mutex);
	print_status(human->name, "is eating", philo);
	better_sleep(philo->eat_time);
	pthread_mutex_lock(&human->stop_mutex);
	if (human->meals != -1 && --human->meals == 0)
		human->stop = 1;
	pthread_mutex_unlock(&human->stop_mutex);
}

void	start_sleeping(t_human *human, t_philo *philo)
{
	print_status(human->name, "is sleeping", philo);
	better_sleep(philo->sleep_time);
}