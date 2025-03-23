/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 04:17:31 by gstitou           #+#    #+#             */
/*   Updated: 2025/03/23 16:30:26 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_active(t_philo *philo)
{
	int	required_meals;
	int	still_active;

	required_meals = philo->data->num_times_to_eat;
	if (required_meals < 0)
		return (1);
	pthread_mutex_lock(&philo->data->meal_mutex);
	still_active = (philo->meals_eaten < required_meals);
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (still_active);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_of_philos == 1)
	{
		take_forks(philo);
		return (NULL);
	}
	if ((philo->id) % 2)
		usleep(1000);
	while (!is_simulation_stopped(philo->data))
	{
		take_forks(philo);
		eat_action(philo);
		if (is_active(philo))
		{
			sleep_action(philo);
			think_action(philo);
		}
		else
			break ;
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	i = 0;
	while (1)
	{
		if (all_philosophers_satisfied(philos))
		{
			stop_simulation(philos->data);
			return (NULL);
		}
		if (check_philosopher_death(&philos[i]))
		{
			pthread_mutex_lock(&philos[i].data->print_mutex);
			printf("%ld %d %s\n", get_time_ms() - philos[i].data->start_time,
				philos[i].id, "is died");
			pthread_mutex_unlock(&philos[i].data->print_mutex);
			return (NULL);
		}
		i = (i + 1) % philos->data->num_of_philos;
		usleep(1000);
	}
	return (NULL);
}

int	start_simulation(t_philo *philosophers)
{
	int			i;
	t_data		*data;
	pthread_t	monitor;

	data = philosophers[0].data;
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&philosophers[i].thread, NULL, &philosopher_routine,
				&philosophers[i]))
			return (0);
		i++;
	}
	if (pthread_create(&monitor, NULL, &monitor_routine, philosophers) != 0)
		return (0);
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (1);
}
