/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoutman <shoutman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 11:15:38 by shoutman          #+#    #+#             */
/*   Updated: 2026/08/17 09:20:04 by shoutman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_philos(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (i < data->nb_philos)
	{
		ret = pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]);
		if (ret != 0)
			break ;
		i++;
	}
	if (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->lock);
		data->stop = 1;
		pthread_mutex_unlock(&data->lock);
		while (--i >= 0)
			pthread_join(data->philos[i].thread, NULL);
		return (1);
	}
	return (0);
}

void	join_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	run_simulation(t_data *data)
{
	data->forks = NULL;
	data->philos = NULL;
	if (init_data(data))
	{
		destroy_data(data);
		return (1);
	}
	if (start_philos(data))
	{
		destroy_data(data);
		return (1);
	}
	monitor_loop(data);
	join_philos(data);
	destroy_data(data);
	return (0);
}
