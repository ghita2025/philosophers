/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:03:39 by gstitou           #+#    #+#             */
/*   Updated: 2025/03/13 02:20:48 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	*philosophers;
	t_data	*data;

	if (ac < 5 || ac > 6)
		return (write(1, "Error: wrong number of arguments\n", 34), 1);
	if (!validate_args(ac, av))
		return (write(1, "Error: invalid arguments format\n", 33), 1);
	data = init_data(av);
	if (!data)
		return (1);
	philosophers = init_philosophers(data);
	if (!philosophers)
		return (free(data->forks), free(data), 1);
	if (!start_simulation(philosophers))
		write(2, "Error: Failed to start simulation\n", 34);
	cleanup(philosophers);
	return (0);
}
