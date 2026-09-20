/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoutman <shoutman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 09:15:23 by shoutman          #+#    #+#             */
/*   Updated: 2026/08/19 16:40:47 by shoutman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	long			meals_eaten;
	long			last_meal;
	pthread_mutex_t	meal_lock;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

struct s_data
{
	int				nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	int				stop;
	t_philo			*philos;
};

int		parse_args(int argc, char **argv, t_data *data);
long	get_time_ms(void);
void	precise_sleep(t_data *data, long ms);
int		init_data(t_data *data);
void	destroy_data(t_data *data);
int		is_stopped(t_data *data);
void	print_status(t_philo *philo, const char *msg);
void	print_death(t_philo *philo);
void	monitor_loop(t_data *data);
void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);
void	*philo_routine(void *arg);
int		start_philos(t_data *data);
void	join_philos(t_data *data);
int		run_simulation(t_data *data);

#endif
