/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:45:30 by gstitou           #+#    #+#             */
/*   Updated: 2025/03/23 17:50:36 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_philo *philo, char *action)
{
	time_t	current_time;

	current_time = get_time_ms();
	sem_wait(philo->data->print_semaphore);
	printf("%ld %d %s\n", current_time - philo->data->start_time, philo->id,
		action);
	sem_post(philo->data->print_semaphore);
}

void	take_forks(t_philo *philo)
{
	if (philo->data->num_of_philos == 1)
	{
		sem_wait(philo->data->forks);
		print_status(philo, "has taken a fork");
		precise_sleep(philo->data->time_to_die);
		sem_post(philo->data->forks);
		return ;
	}
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
}

void	eat_action(t_philo *philo)
{
	print_status(philo, "is eating");
	sem_wait(philo->data->meal_semaphore);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	sem_post(philo->data->meal_semaphore);
	precise_sleep(philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	sleep_action(t_philo *philo)
{
	print_status(philo, "is sleeping");
	precise_sleep(philo->data->time_to_sleep);
}

void	think_action(t_philo *philo)
{
	if (philo->data->num_of_philos % 2 != 0)
		usleep(500);
	print_status(philo, "is thinking");
}
