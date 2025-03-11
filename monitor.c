/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 05:37:28 by gstitou           #+#    #+#             */
/*   Updated: 2025/03/11 01:38:21 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_stopped(t_data *data)
{
	int	stopped;

	pthread_mutex_lock(&data->simulation_mutex);
	stopped = data->simulation_stop;
	pthread_mutex_unlock(&data->simulation_mutex);
	return (stopped);
}

void	stop_simulation(t_data *data)
{
	pthread_mutex_lock(&data->simulation_mutex);
	data->simulation_stop = 1;
	pthread_mutex_unlock(&data->simulation_mutex);
}

int	check_philosopher_death(t_philo *philo)
{
	time_t	current_time;
	time_t	time_since_last_meal;

	// if (is_simulation_stopped(philo->data))
	// 	return (0);

	current_time = get_time_ms();
	pthread_mutex_lock(&philo->data->meal_mutex);
	time_since_last_meal = current_time - philo->last_meal_time;
	pthread_mutex_unlock(&philo->data->meal_mutex);

	if (time_since_last_meal >= philo->data->time_to_die)
	{
		stop_simulation(philo->data);
		return (1);
	}
	return (0);
}

int	all_philosophers_satisfied(t_philo *philosophers)
{
	int	i;
	int	all_ate_enough;
	int	required_meals;

	required_meals = philosophers[0].data->num_times_to_eat;
	all_ate_enough = 1;
	i = 0;
	while (i < philosophers[0].data->num_of_philos)
	{
		pthread_mutex_lock(&philosophers[0].data->meal_mutex);
		if (philosophers[i].meals_eaten != required_meals)
			all_ate_enough = 0;
		pthread_mutex_unlock(&philosophers[0].data->meal_mutex);
		
		if (!all_ate_enough)
			break ;
		i++;
	}
	return (all_ate_enough);
}

void	cleanup(t_philo *philosophers)
{
	int		i;
	t_data	*data;

	data = philosophers[0].data;
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->simulation_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	free(data->forks);
	free(data);
	free(philosophers);
}
