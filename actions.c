/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 04:47:35 by gstitou           #+#    #+#             */
/*   Updated: 2025/03/11 02:43:34 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_status(t_philo *philo, char *action)
{
    time_t current_time;
    // if (is_simulation_stopped(philo->data))
    //     return ;
    current_time = get_time_ms() - philo->data->start_time;
    pthread_mutex_lock(&philo->data->print_mutex);
   // if (!is_simulation_stopped(philo->data))
        printf("%ld %d %s\n", current_time, philo->id, action);
    pthread_mutex_unlock(&philo->data->print_mutex);
}
void take_forks(t_philo *philo)
{
    time_t current_time;
    if (philo->data->num_of_philos == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taking a fork");
        precise_sleep(philo->data->time_to_die);
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    if (philo->id % 2 != 0)
    {
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taking a fork");
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taking a fork");
    }
    else
    {
        usleep(100);
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taking a fork");
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taking a fork");
    }
}
void eat_action(t_philo *philo)
{
    print_status(philo, "is eating");
    pthread_mutex_lock(&philo->data->meal_mutex);
    philo->last_meal_time = get_time_ms();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->data->meal_mutex);
    precise_sleep(philo->data->time_to_eat);
    if (philo->id != 2)
    {
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
    }
    else
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
    }
}
void sleep_action(t_philo *philo)
{
    print_status(philo, "is sleeping");
    precise_sleep(philo->data->time_to_sleep);
}

void think_action(t_philo *philo)
{
    print_status(philo, "is thinking");
}