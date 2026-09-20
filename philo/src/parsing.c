/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoutman <shoutman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 11:20:34 by shoutman          #+#    #+#             */
/*   Updated: 2026/08/14 11:45:52 by shoutman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_valid_number(const char *str)
{
	int	i;

	if (str[0] == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static long	ft_atol(const char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

static int	check_args(int argc, char **argv, long *values)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		if (!ft_is_valid_number(argv[i + 1]))
			return (1);
		values[i] = ft_atol(argv[i + 1]);
		if (values[i] <= 0)
			return (1);
		if (i == 0 && values[i] > INT_MAX)
			return (1);
		i++;
	}
	return (0);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	long	values[5];

	if (argc != 5 && argc != 6)
		return (1);
	if (check_args(argc, argv, values))
		return (1);
	data->nb_philos = (int)values[0];
	data->time_to_die = values[1];
	data->time_to_eat = values[2];
	data->time_to_sleep = values[3];
	if (argc == 6)
		data->must_eat = values[4];
	else
		data->must_eat = -1;
	return (0);
}
