/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoutman <shoutman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 09:16:08 by shoutman          #+#    #+#             */
/*   Updated: 2026/08/19 16:42:19 by shoutman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_args(argc, argv, &data))
	{
		printf("Error: invalid arguments\n");
		printf("Usage: %s nb_philos time_to_die time_to_eat time_to_sleep"
			" [nb_times_must_eat]\n", argv[0]);
		return (1);
	}
	if (run_simulation(&data))
	{
		printf("Error: simulation failed to start\n");
		return (1);
	}
	return (0);
}
