/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:21:03 by gstitou           #+#    #+#             */
/*   Updated: 2025/03/20 17:40:19 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(char **av)
{
	int		i;
	t_data	*data;

	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (write(1, "Error: Malloc failed\n", 22), NULL);
	data->num_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
    {
        data->num_times_to_eat = ft_atoi(av[5]);
        if (!data->num_times_to_eat)
            return (NULL);
    }
	else
		data->num_times_to_eat = -1;
	data->simulation_stop = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		return (free(data), write(1, "Error: Malloc failed\n", 22), NULL);
	pthread_mutex_init(&data->simulation_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	while (i < data->num_of_philos)
		pthread_mutex_init(&data->forks[i++], NULL);
	gettimeofday(&data->start_times,NULL);
	return (data);
}
t_philo	*init_philosophers(t_data *data)
{
	t_philo	*philosophers;
	int		i;

	philosophers = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!philosophers)
		return (NULL);
	data->start_time = get_time_ms();
	i = 0;
	while (i < data->num_of_philos)
	{
		philosophers[i].id = i + 1;
		philosophers[i].last_meal_time = data->start_time;
		philosophers[i].meals_eaten = 0;
		philosophers[i].data = data;
		philosophers[i].left_fork = &data->forks[i];
		if (data->num_of_philos == 1)
			philosophers[i].right_fork = NULL;
		else
			philosophers[i].right_fork = &data->forks[(i + 1)% data->num_of_philos];
		i++;
	}
	return (philosophers);
}
