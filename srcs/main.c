/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:54:40 by jpeyron           #+#    #+#             */
/*   Updated: 2021/11/14 20:07:47 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(t_data *data, int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (!is_number(av[i]))
		{
			printf("%s is not a number!\n", av[i]);
			return (0);
		}
	}
	memset(data, 0, sizeof(t_data));
	data->nb_philo = ft_atoi(av[1]);
	data->ttd = ft_atoi(av[2]);
	data->tte = ft_atoi(av[3]);
	data->tts = ft_atoi(av[4]);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->finished_mutex, NULL);
	if (ac > 5)
		data->meals = ft_atoi(av[5]);
	else
		data->meals = -1;
	return (1);
}

int	setup_philos(t_data *data)
{
	int	i;

	i = -1;
	data->philos = malloc(data->nb_philo * sizeof(t_philo));
	if (!data->philos)
		return (0);
	memset(data->philos, 0, data->nb_philo * sizeof(t_philo));
	while (++i < data->nb_philo)
	{
		data->philos[i].name = i + 1;
		data->philos[i].meals = -1;
		data->philos[i].data = data;
		data->philos[i].next_fork = i + 1;
		gettimeofday(&data->philos[i].last_meal, NULL);
		if (data->meals != -1)
			data->philos[i].meals = data->meals;
		if (i + 1 == data->nb_philo)
			data->philos[i].next_fork = 0;
		pthread_mutex_init(&data->philos[i].fork_mutex, NULL);
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
	}
	return (1);
}

void	print_status(int name, char *msg, t_data *data)
{
	long	time;

	if (data->stop)
		return ;
	time = millis_time_since(data->started);
	pthread_mutex_lock(&data->print_mutex);
	printf("%ldms %d %s\n", time, name, msg); //penser a retirer le ms
	pthread_mutex_unlock(&data->print_mutex);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;

	data = malloc(sizeof(t_data));
	i = -1;
	if (!data || !init_args(data, ac, av))
	{
		if (data)
			pthread_mutex_destroy(&data->print_mutex);
		free(data);
		return (0);
	}
	setup_philos(data);
	start_simulation(data);
	while (++i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->philos[i].fork_mutex);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->finished_mutex);
	free(data->philos);
	free(data);
	return (0);
}
