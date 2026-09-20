/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoutman <shoutman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 10:30:41 by shoutman          #+#    #+#             */
/*   Updated: 2026/08/18 14:10:26 by shoutman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].meal_lock, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_data(t_data *data)
{
	data->start_time = get_time_ms();
	data->stop = 0;
	if (pthread_mutex_init(&data->lock, NULL) != 0)
		return (1);
	if (init_forks(data))
		return (1);
	if (init_philos(data))
		return (1);
	return (0);
}

void	destroy_data(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data->philos)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_destroy(&data->philos[i].meal_lock);
			i++;
		}
	}
	pthread_mutex_destroy(&data->lock);
	free(data->philos);
}
