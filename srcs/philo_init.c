/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <jpeyron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:58:10 by jpeyron           #+#    #+#             */
/*   Updated: 2021/10/20 18:37:25 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_philo *philo)
{
	int	i;

	i = -1;
	if (gettimeofday(&philo->started, NULL))
		return (0);
	philo->humans = malloc(philo->nb_philo * sizeof(t_human));
	if (!philo->humans)
		return (0);
	memset(philo->humans, 0, philo->nb_philo * sizeof(t_human));
	while (++i < philo->nb_philo)
		philo->humans[i].name = i;
	return (1);
}