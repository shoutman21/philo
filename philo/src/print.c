/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoutman <shoutman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 09:50:09 by shoutman          #+#    #+#             */
/*   Updated: 2026/08/19 15:30:33 by shoutman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	append_nbr(char *buf, int i, long n)
{
	char	tmp[20];
	int		j;

	j = 0;
	if (n == 0)
		tmp[j++] = '0';
	while (n > 0)
	{
		tmp[j++] = '0' + (n % 10);
		n /= 10;
	}
	while (j > 0)
		buf[i++] = tmp[--j];
	return (i);
}

static int	append_str(char *buf, int i, const char *str)
{
	int	j;

	j = 0;
	while (str[j])
		buf[i++] = str[j++];
	return (i);
}

int	is_stopped(t_data *data)
{
	int	stopped;

	pthread_mutex_lock(&data->lock);
	stopped = data->stop;
	pthread_mutex_unlock(&data->lock);
	return (stopped);
}

void	print_status(t_philo *philo, const char *msg)
{
	char	buf[64];
	int		i;

	pthread_mutex_lock(&philo->data->lock);
	if (!philo->data->stop)
	{
		i = append_nbr(buf, 0, get_time_ms() - philo->data->start_time);
		i = append_str(buf, i, " ");
		i = append_nbr(buf, i, philo->id);
		i = append_str(buf, i, " ");
		i = append_str(buf, i, msg);
		i = append_str(buf, i, "\n");
		write(1, buf, i);
	}
	pthread_mutex_unlock(&philo->data->lock);
}

void	print_death(t_philo *philo)
{
	char	buf[64];
	int		i;

	pthread_mutex_lock(&philo->data->lock);
	philo->data->stop = 1;
	i = append_nbr(buf, 0, get_time_ms() - philo->data->start_time);
	i = append_str(buf, i, " ");
	i = append_nbr(buf, i, philo->id);
	i = append_str(buf, i, " died\n");
	write(1, buf, i);
	pthread_mutex_unlock(&philo->data->lock);
}
