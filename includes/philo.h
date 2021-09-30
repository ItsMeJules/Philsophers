/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <jpeyron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:54:37 by jpeyron           #+#    #+#             */
/*   Updated: 2021/09/30 17:19:26 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

/*
** UTILS/utils.c
*/
int	is_number(char *str);
int	ft_atoi(const char *str);

/*
** UTILS/memory_utils.c
*/
void	free_all(t_philo *philo);

typedef struct s_human
{
	int	forks;
	int	thinking;
	int	sleeping;
	int	eating;
	int	dead;
	int	last_meal;
}	t_human;

typedef struct s_philo
{
	int		nb_philo;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		must_eat_nb;
	t_human	*humans;
}	t_philo;

#endif