/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoutman <shoutman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 09:45:21 by shoutman          #+#    #+#             */
/*   Updated: 2026/08/17 10:10:47 by shoutman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	get_meal_info(t_philo *philo, long *last, long *meals)
{
	pthread_mutex_lock(&philo->meal_lock);
	*last = philo->last_meal;
	*meals = philo->meals_eaten;
	pthread_mutex_unlock(&philo->meal_lock);
}

static int	check_philo(t_philo *philo)
{
	long	last;
	long	meals;

	get_meal_info(philo, &last, &meals);
	if (get_time_ms() - last > philo->data->time_to_die)
	{
		print_death(philo);
		return (1);
	}
	if (philo->data->must_eat >= 0 && meals < philo->data->must_eat)
		return (-1);
	return (0);
}

static int	check_all_philos(t_data *data)
{
	int	i;
	int	all_done;
	int	res;

	i = 0;
	all_done = 1;
	while (i < data->nb_philos)
	{
		res = check_philo(&data->philos[i]);
		if (res == 1)
			return (1);
		if (res == -1)
			all_done = 0;
		i++;
	}
	if (all_done && data->must_eat >= 0)
	{
		pthread_mutex_lock(&data->lock);
		data->stop = 1;
		pthread_mutex_unlock(&data->lock);
		return (1);
	}
	return (0);
}

void	monitor_loop(t_data *data)
{
	while (!is_stopped(data))
	{
		if (check_all_philos(data))
			return ;
		usleep(1000);
	}
}
