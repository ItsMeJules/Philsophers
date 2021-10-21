/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <jpeyron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:54:37 by jpeyron           #+#    #+#             */
/*   Updated: 2021/10/21 18:25:56 by jpeyron          ###   ########.fr       */
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

typedef struct s_philo
{
	int				nb_philo;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat_nb;
	t_human			*humans;
}	t_philo;

typedef struct s_human
{
	int				name;
	int				thinking;
	int				sleeping;
	int				eating;
	int				dead;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_t		*thread;
	struct timeval	last_meal;
	struct timeval	started;
	struct s_philo	*philo;
}	t_human;

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
void	*philo_routine(void *arg);
int		check_at_philos(t_philo *philo);
int		start_philos(t_philo *philo);

#endif