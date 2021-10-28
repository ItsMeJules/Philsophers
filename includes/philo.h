/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <jpeyron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:54:37 by jpeyron           #+#    #+#             */
/*   Updated: 2021/10/27 17:16:28 by jpeyron          ###   ########.fr       */
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
	int				error;
	struct timeval	started;
	struct s_human	*humans;
	pthread_t		thread;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	error_mutex;
}	t_philo;

typedef struct s_human
{
	int				name;
	int				meals;
	int				stop;
	struct timeval	last_meal;
	struct s_philo	*philo;
	pthread_mutex_t	fork_mutex;
	pthread_t		thread;
}	t_human;

/*
** UTILS/utils.c
*/
int		is_number(char *str);
int		ft_atoi(const char *str);
long	millis_time_since(struct timeval time);
int		better_sleep(long sleep_ms);
void	init_ret_error(t_philo *philo, int error);

/*
** UTILS/memory_utils.c
*/
void	free_all(t_philo *philo);

/*
** philo_init.c
*/
int		init_philos(t_philo *philo);
void	*philo_routine(void *arg);
void	*philo_watcher(void *arg);
int		start_philos(t_philo *philo);

/*
** philo_status.c
*/
int	print_status(int name, char *msg, t_philo *philo);
int	take_forks(t_human *human, t_human *h_tab);
int	drop_forks(t_human *human, t_human *h_tab);
int	start_eating(t_human *human, t_philo *philo);
int	start_sleeping(t_human *human, t_philo *philo);

#endif