/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:54:42 by jpeyron           #+#    #+#             */
/*   Updated: 2021/11/14 20:15:04 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;
	int	num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

long	millis_time_since(struct timeval time)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec - time.tv_sec) * 1000
		+ (current.tv_usec - time.tv_usec) / 1000);
}

int	better_sleep(long sleep_ms, t_philo *philo)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	while (millis_time_since(current) < sleep_ms)
	{
		if (should_stop(philo->data))
			return (1);
		usleep(100);
	}
	return (0);
}

int	should_stop(t_data *data)
{
	int	stop;
	
	pthread_mutex_lock(&data->finished_mutex);
	pthread_mutex_lock(&data->stop_mutex);
	if (!data->stop && data->finished == data->nb_philo)
		stop = 1;
	else
		stop = data->stop;
	pthread_mutex_unlock(&data->finished_mutex);
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}