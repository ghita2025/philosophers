/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 04:17:31 by gstitou           #+#    #+#             */
/*   Updated: 2025/03/18 15:08:21 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_active(t_philo *philo)
{
    int required_meals;
    int checker;

    checker = 1;
    required_meals = philo->data->num_times_to_eat;
    pthread_mutex_lock(&philo->data->meal_mutex);
    if (philo->meals_eaten == required_meals)
        checker = 0;
    pthread_mutex_unlock(&philo->data->meal_mutex);
    return (checker);
}
void *philosopher_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->data->num_of_philos == 1)
    {
        take_forks(philo);
        return (NULL);
    }
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
            break;
    }
    return (NULL);
}
void *monitor_routine(void *arg)
{
    t_philo *philosophers;
    int i;

    philosophers = (t_philo *)arg;
    i = 0;
    while (i < philosophers->data->num_of_philos)
    {
        if (all_philosophers_satisfied(philosophers))
        {
            stop_simulation(philosophers->data);
            return (NULL);
        }
        if (check_philosopher_death(&philosophers[i]))
        {
            pthread_mutex_lock(&philosophers[i].data->print_mutex);
            printf("%ld %d %s\n", get_time_ms() - philosophers[i].data->start_time, philosophers[i].id,
                   "is died");
            pthread_mutex_unlock(&philosophers[i].data->print_mutex);
            return (NULL);
        }
    }
    i++;
    if (i == philosophers->data->num_of_philos)
        i = 0;
    //}
    // usleep(1000);
     return (NULL);
}

int start_simulation(t_philo *philosophers)
{
    int i;
    t_data *data;

    pthread_t monitor;
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
