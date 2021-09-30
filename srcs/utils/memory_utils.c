/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <jpeyron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:55:25 by jpeyron           #+#    #+#             */
/*   Updated: 2021/09/30 17:28:04 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		free(&philo->humans[i]);
		i++;
	}
	free(philo);
}