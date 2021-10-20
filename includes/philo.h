/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <jpeyron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:54:37 by jpeyron           #+#    #+#             */
/*   Updated: 2021/10/01 14:10:13 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

/*
** UTILS/utils.c
*/
int		is_number(char *str);
int		ft_atoi(const char *str);

/*
** UTILS/memory_utils.c
*/
void	free_all(t_philo *philo);

typedef struct s_human
{
	int			name;
	int			forks;
	int			thinking;
	int			sleeping;
	int			eating;
	int			dead;
	int			last_meal;
	pthread_t	*thread;
}	t_human;

typedef struct s_philo
{
	int				nb_philo;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat_nb;
	t_human			*humans;
	struct timeval	*tv;
}	t_philo;

#endif