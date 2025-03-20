/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:45:50 by gstitou           #+#    #+#             */
/*   Updated: 2025/03/20 16:57:44 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *meal_monitor(void *arg)
{
	t_data *data;
	int i;

	data = (t_data *)arg;
	i = 0;
	while (i < data->num_of_philos)
	{
		sem_wait(data->all_eat_sem);
		i++;
	}
	sem_post(data->death_semaphore);
	return (NULL);
}

void wait_for_termination(t_philo *philo)
{
	pthread_t thread;
	int i;
	t_data *data;

	data = philo->data;

	if (data->num_times_to_eat > 0)
	{
		if (pthread_create(&thread, NULL, &meal_monitor, data) != 0)
		{
			write(1, "Error: Thread creation failed\n", 30);
			return;
		}
		pthread_detach(thread);
	}
	sem_wait(data->death_semaphore);
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
	// if (data->num_of_philos > 0)
	// 	pthread_join(thread, NULL);
}

void create_processes(t_philo *philo, int i)
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
		exit(0);
	}
}

int main(int ac, char **av)
{
	t_data *data;
	t_philo *philosopher;
	int i;

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
