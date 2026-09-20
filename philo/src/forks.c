/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoutman <shoutman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 11:00:16 by shoutman          #+#    #+#             */
/*   Updated: 2026/08/19 16:00:39 by shoutman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->left_fork;
	second = philo->right_fork;
	if (first > second)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	if (second != first)
		pthread_mutex_lock(second);
	print_status(philo, "has taken a fork");
	if (second != first)
		print_status(philo, "has taken a fork");
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	if (philo->right_fork != philo->left_fork)
		pthread_mutex_unlock(philo->right_fork);
}
