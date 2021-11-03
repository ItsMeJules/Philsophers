/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <jpeyron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:55:25 by jpeyron           #+#    #+#             */
/*   Updated: 2021/11/03 18:15:12 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_mutex_destroy(&philo->humans[i].fork_mutex);
		pthread_mutex_destroy(&philo->humans[i].meal_mutex);
		pthread_mutex_destroy(&philo->humans[i].stop_mutex);
		i++;
	}
	pthread_mutex_destroy(&philo->print_mutex);
	free(philo->humans);
	free(philo);
}