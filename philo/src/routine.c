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
	usleep(philo->data->time_to_eat * 1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philos == 1)
	{
		take_forks(philo);
		while (!is_stopped(philo->data))
			usleep(1000);
		release_forks(philo);
		return (NULL);
	}
	while (!is_stopped(philo->data))
	{
		print_status(philo, "is thinking");
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		print_status(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}
