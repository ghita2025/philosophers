/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:45:53 by gstitou           #+#    #+#             */
/*   Updated: 2025/03/20 17:03:11 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *monitor_routine(void *arg)
{
    t_philo *philosopher;
    philosopher = (t_philo *)arg;

    while (1)
    {
        if (check_philosopher_death(philosopher))
        {
            sem_wait(philosopher->data->print_semaphore);
            printf("%ld %d %s\n", get_time_ms() - philosopher->data->start_time,
                   philosopher->id, "died");
            sem_post(philosopher->data->death_semaphore);
            return (NULL);
        }
       // usleep(500);
    }
    return (NULL);
}

void start_simulation(t_philo *philo)
{
    pthread_t monitor;

    if (pthread_create(&monitor, NULL, &monitor_routine, philo) != 0)
    {
        write(1, "Error: Thread creation failed\n", 30);
        exit(1);
    }
    pthread_detach(monitor);
    if (philo->data->num_of_philos == 1)
    {
        take_forks(philo);
        return;
    }
    while (1)
    {
        take_forks(philo);
        eat_action(philo);
        if (is_active(philo))
        {
            sleep_action(philo);
            think_action(philo);
        }
        else
        {
            sem_post(philo->data->all_eat_sem);
            break;
        }
    }
}
