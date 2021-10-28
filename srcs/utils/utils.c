/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <jpeyron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:54:42 by jpeyron           #+#    #+#             */
/*   Updated: 2021/10/27 17:09:09 by jpeyron          ###   ########.fr       */
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

	if (gettimeofday(&current, NULL))
		return (-1);
	return ((current.tv_sec - time.tv_sec) * 1000
		+ (current.tv_usec - time.tv_usec) / 1000);
}

int	better_sleep(long sleep_ms)
{
	struct timeval	current;

	if (gettimeofday(&current, NULL))
		return (1);
	while (millis_time_since(current) < sleep_ms)
		usleep(100);
	return (0);
}

void	init_ret_error(t_philo *philo, int error)
{
	pthread_mutex_lock(&philo->error_mutex);
	philo->error = error;
	pthread_mutex_unlock(&philo->error_mutex);
}
