/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <jpeyron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:43:47 by jpeyron           #+#    #+#             */
/*   Updated: 2021/10/27 17:10:07 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_status(int name, char *msg, t_philo *philo)
{
	long	time;

	time = millis_time_since(philo->started);
	if (time == -1)
		return (1);
	if (pthread_mutex_lock(&philo->print_mutex))
		return (1);
	printf("%ldms %d %s\n", time, name, msg);
	if (pthread_mutex_unlock(&philo->print_mutex))
		return (1);
	return (0);
}

int	take_forks(t_human *human, t_human *h_tab)
{
	int		right_ph;

	right_ph = human->name; //Tab starts at 0 and the philo name starts at 1
	if (human->name == human->philo->nb_philo)
		right_ph = 0;
	if (pthread_mutex_lock(&human->fork_mutex))
		return (1);
	print_status(human->name, "has taken a fork", human->philo);
	if (pthread_mutex_lock(&h_tab[right_ph].fork_mutex))
		return (1);
	print_status(human->name, "has taken a fork", human->philo);
	return (0);
}

int	drop_forks(t_human *human, t_human *h_tab)
{
	int	right_ph;
	
	right_ph = human->name; //Tab starts at 0 and the philo name starts at 1
	if (human->name == human->philo->nb_philo)
		right_ph = 0;
	if (pthread_mutex_unlock(&human->fork_mutex))
		return (1);
	if (pthread_mutex_unlock(&h_tab[right_ph].fork_mutex))
		return (1);
	return (0);
}

int	start_eating(t_human *human, t_philo *philo)
{
	if (gettimeofday(&human->last_meal, NULL))
		return (1);
	human->meals++;
	print_status(human->name, "is eating", philo);
	if (better_sleep(philo->eat_time))
		return (1);
	return (0);
}

int	start_sleeping(t_human *human, t_philo *philo)
{
	print_status(human->name, "is sleeping", philo);
	if (better_sleep(philo->sleep_time))
		return (1);
	return (0);
}