/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:45:47 by gstitou           #+#    #+#             */
/*   Updated: 2025/03/23 17:51:23 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_active(t_philo *philosopher)
{
	int	required_meals;
	int	still_active;

	required_meals = philosopher->data->num_times_to_eat;
	if (required_meals < 0)
		return (1);
	sem_wait(philosopher->data->meal_semaphore);
	still_active = (philosopher->meals_eaten < required_meals);
	sem_post(philosopher->data->meal_semaphore);
	return (still_active);
}

int	check_philosopher_death(t_philo *philo)
{
	time_t	current_time;
	time_t	time_since_last_meal;

	current_time = get_time_ms();
	sem_wait(philo->data->meal_semaphore);
	time_since_last_meal = current_time - philo->last_meal_time;
	sem_post(philo->data->meal_semaphore);
	if (time_since_last_meal > philo->data->time_to_die)
	{
		return (1);
	}
	return (0);
}

void	cleanup(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	close_semaphores(data);
	unlink_semaphore();
	free(data->pid);
	free(data);
	free(philo);
}
