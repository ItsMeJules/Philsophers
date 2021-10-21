/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <jpeyron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:54:37 by jpeyron           #+#    #+#             */
/*   Updated: 2021/10/21 15:31:33 by jpeyron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_human
{
	int				name;
	int				forks;
	int				thinking;
	int				sleeping;
	int				eating;
	int				dead;
	long			last_meal;
	pthread_t		*thread;
}	t_human;

typedef struct s_philo
{
	int				nb_philo;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat_nb;
	t_human			*humans;
	struct timeval	started;
}	t_philo;

/*
** UTILS/utils.c
*/
int		is_number(char *str);
int		ft_atoi(const char *str);
long	millis_time_since(struct timeval time);

/*
** UTILS/memory_utils.c
*/
void	free_all(t_philo *philo);

/*
** philo_init.c
*/
int		init_philos(t_philo *philo);
void	philo_routine(t_human *human);
int		check_at_philos(t_philo *philo)
int		start_philos(t_philo *philo);

#endif