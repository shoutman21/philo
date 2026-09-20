/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoutman <shoutman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 10:40:55 by shoutman          #+#    #+#             */
/*   Updated: 2026/08/19 15:50:12 by shoutman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_status(philo, "is eating");
	precise_sleep(philo->data, philo->data->time_to_eat);
}

static void	lone_philo(t_philo *philo)
{
	take_forks(philo);
	while (!is_stopped(philo->data))
		usleep(1000);
	release_forks(philo);
}

static void	think(t_philo *philo)
{
	long	gap;

	print_status(philo, "is thinking");
	gap = philo->data->time_to_die - philo->data->time_to_eat
		- philo->data->time_to_sleep;
	if (gap < 0)
		gap = 0;
	precise_sleep(philo->data, gap / 2);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philos == 1)
	{
		lone_philo(philo);
		return (NULL);
	}
	print_status(philo, "is thinking");
	if (philo->id % 2 == 0)
		precise_sleep(philo->data, philo->data->time_to_eat / 2);
	while (!is_stopped(philo->data))
	{
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		print_status(philo, "is sleeping");
		precise_sleep(philo->data, philo->data->time_to_sleep);
		think(philo);
	}
	return (NULL);
}
