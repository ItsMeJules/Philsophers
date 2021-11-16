/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeyron <jpeyron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:54:37 by jpeyron           #+#    #+#             */
/*   Updated: 2021/11/16 15:42:27 by jpeyron          ###   ########.fr       */
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

typedef struct s_data
{
	int				nb_philo;
	int				ttd;
	int				tte;
	int				tts;
	int				meals;
	int				stop;
	int				finished;
	struct timeval	started;
	struct s_philo	*philos;
	pthread_t		thread;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	finished_mutex;
}	t_data;

typedef struct s_philo
{
	int				name;
	int				meals;
	int				next_fork;
	struct timeval	last_meal;
	struct s_data	*data;
	pthread_t		thread;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	meal_mutex;
}	t_philo;

/*
** SRCS/main.c
*/
void	print_status(int name, char *msg, t_data *data);

/*
** SRCS/simulation.c
*/
void	start_simulation(t_data *data);

/*
** UTILS/utils.c
*/
int		is_number(char *str);
int		ft_atoi(const char *str);
long	millis_time_since(struct timeval time);
int		better_sleep(long sleep_ms, t_philo *philo);
int		should_stop(t_data *data);

/*
** UTILS/utils2.c
*/
int		philo_died(t_data *data, t_philo *philo);

/*
** UTILS/memory_utils.c
*/
void	free_all(t_philo *philo);

#endif