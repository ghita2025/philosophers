/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:45:33 by gstitou           #+#    #+#             */
/*   Updated: 2025/03/21 13:55:04 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	creat_semaphores(t_data *data)
{
	unlink_semaphore();
	data->meal_semaphore = sem_open("/meal_semaphore", O_CREAT, 0644, 1);
	data->print_semaphore = sem_open("/print_semaphore", O_CREAT, 0644, 1);
	data->forks = sem_open("/my_forks", O_CREAT, 0644, data->num_of_philos);
	data->death_semaphore = sem_open("/death_semaphore", O_CREAT, 0644, 1);
	data->all_eat_sem = sem_open("/all_eat_sem", O_CREAT, 0644,
			data->num_of_philos);
	if (data->meal_semaphore == SEM_FAILED
		|| data->print_semaphore == SEM_FAILED ||
		data->forks == SEM_FAILED || data->death_semaphore == SEM_FAILED ||
		data->all_eat_sem == SEM_FAILED)
	{
		close_semaphores(data);
		free(data);
		write(1, "Error: Semaphore creation failed\n", 33);
		exit(1);
	}
}

void	unlink_semaphore(void)
{
	sem_unlink("/death_semaphore");
	sem_unlink("/print_semaphore");
	sem_unlink("/meal_semaphore");
	sem_unlink("/all_eat_sem");
	sem_unlink("/my_forks");
}

void	close_semaphores(t_data *data)
{
	if (data->meal_semaphore != SEM_FAILED)
		sem_close(data->meal_semaphore);
	if (data->print_semaphore != SEM_FAILED)
		sem_close(data->print_semaphore);
	if (data->death_semaphore != SEM_FAILED)
		sem_close(data->death_semaphore);
	if (data->forks != SEM_FAILED)
		sem_close(data->forks);
	if (data->all_eat_sem != SEM_FAILED)
		sem_close(data->all_eat_sem);
}

t_data	*init_data(char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (write(1, "Error: Malloc failed\n", 22), NULL);
	data->num_of_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
	{
		data->num_times_to_eat = ft_atol(av[5]);
		if (!data->num_times_to_eat)
			return (NULL);
	}
	else
		data->num_times_to_eat = -1;
	creat_semaphores(data);
	data->pid = malloc(sizeof(pid_t) * data->num_of_philos);
	if (!data->pid)
		return (free(data), NULL);
	return (data);
}

t_philo	*init_philosopher(t_data *data)
{
	t_philo	*philosopher;

	philosopher = malloc(sizeof(t_philo));
	if (!philosopher)
		return (NULL);
	data->start_time = get_time_ms();
	philosopher->last_meal_time = data->start_time;
	philosopher->meals_eaten = 0;
	philosopher->data = data;
	return (philosopher);
}
