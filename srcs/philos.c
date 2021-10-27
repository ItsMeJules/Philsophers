/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <jpeyron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:11:25 by jpeyron           #+#    #+#             */
/*   Updated: 2021/10/27 14:26:09 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_status(int name, char *msg, t_philo *philo)
{
	long	time;

	time = millis_time_since(philo->started);
	if (time == -1)
		return (-1);
	if (pthread_mutex_lock(&philo->print_mutex))
		return (-1);
	printf("%ldms %d %s\n", time, name, msg);
	if (pthread_mutex_unlock(&philo->print_mutex))
		return (-1);
	return (1);
}

int	take_forks(t_human *human, t_human *h_tab)
{
	int		right_ph;

	right_ph = human->name; //Tab starts at 0 and the philo name starts at 1
	if (human->name == human->philo->nb_philo)
		right_ph = 0;
	if (pthread_mutex_lock(&human->fork_mutex))
		return (0);
	print_status(human->name, "has taken a fork", human->philo);
	if (pthread_mutex_lock(&h_tab[right_ph].fork_mutex))
		return (0);
	print_status(human->name, "has taken a fork", human->philo);
	return (1);
}

int	drop_forks(t_human *human, t_human *h_tab)
{
	int	right_ph;
	
	right_ph = human->name; //Tab starts at 0 and the philo name starts at 1
	if (human->name == human->philo->nb_philo)
		right_ph = 0;
	if (pthread_mutex_unlock(&human->fork_mutex))
		return (0);
	print_status(human->name, "dropped a fork", human->philo);
	if (pthread_mutex_unlock(&h_tab[right_ph].fork_mutex))
		return (0);
	print_status(human->name, "dropped a fork", human->philo);
	return (1);
}

int	start_eating(t_human *human)
{
	if (gettimeofday(&human->last_meal, NULL))
		return (0);
	human->meals++;
	print_status(human->name, "is eating", human->philo);
	better_sleep(human->philo->eat_time);
	return (1);
}

int	start_sleeping(t_human *human)
{
	(void)human;
	return (0);
}