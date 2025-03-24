/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:45:50 by gstitou           #+#    #+#             */
/*   Updated: 2025/03/24 12:09:06 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_for_termination(t_philo *philo)
{
	int		i;
	t_data	*data;

	data = philo->data;
	while (1)
	{
		if (data->death_semaphore->__align == 0
			|| data->all_eat_sem->__align == 0)
			break ;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		kill(data->pid[i], SIGKILL);
		i++;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		waitpid(data->pid[i], NULL, 0);
		i++;
	}
}

void	create_processes(t_philo *philo, int i)
{
	philo->data->pid[i] = fork();
	if (philo->data->pid[i] < 0)
	{
		free(philo->data->pid);
		free(philo->data);
		free(philo);
		write(1, "Error: fork failed\n", 20);
		exit(EXIT_FAILURE);
	}
	else if (philo->data->pid[i] == 0)
	{
		philo->id = i + 1;
		start_simulation(philo);
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philosopher;
	int		i;

	if (ac < 5 || ac > 6)
		return (write(1, "Error: wrong number of arguments\n", 34), 1);
	if (!validate_args(ac, av))
		return (write(1, "Error: invalid arguments format\n", 33), 1);
	data = init_data(av);
	if (!data)
		return (1);
	philosopher = init_philosopher(data);
	if (!philosopher)
		return (free(data), 1);
	i = 0;
	while (i < data->num_of_philos)
	{
		create_processes(philosopher, i);
		i++;
	}
	wait_for_termination(philosopher);
	cleanup(philosopher);
	return (0);
}
