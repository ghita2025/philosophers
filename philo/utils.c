/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 04:09:12 by gstitou           #+#    #+#             */
/*   Updated: 2025/03/23 15:48:50 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*globale(void)
{
	static t_philo	philo;

	return (&philo);
}

time_t	get_time_ms(void)
{
	t_time	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	precise_sleep(time_t duration, t_data *data)
{
	time_t	start_time;

	start_time = get_time_ms();
	while (get_time_ms() - start_time < duration)
	{
		pthread_mutex_lock(&data->simulation_mutex);
		if (data->simulation_stop)
		{
			pthread_mutex_unlock(&data->simulation_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->simulation_mutex);
		usleep(500);
	}
}
