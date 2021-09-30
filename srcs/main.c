/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <jpeyron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:54:40 by jpeyron           #+#    #+#             */
/*   Updated: 2021/09/30 17:20:44 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(t_philo *philo, int ac, char **av)
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
	philo->nb_philo = ft_atoi(av[1]);
	philo->die_time = ft_atoi(av[2]);
	philo->eat_time = ft_atoi(av[3]);
	philo->sleep_time = ft_atoi(av[4]);
	philo->must_eat_nb = 0;
	if (ac > 5)
		philo->must_eat_nb = ft_atoi(av[5]);
	philo->humans = malloc(philo->nb_philo * sizeof(t_human));
	memset(philo->humans, 0, philo->nb_philo * sizeof(t_human));
	if (!philo->humans)
	{
		free(philo);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo || !init_args(philo, ac, av))
		return (0);
	free_all(philo);
	return (0);
}
