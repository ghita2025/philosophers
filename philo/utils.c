/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 04:09:12 by gstitou           #+#    #+#             */
/*   Updated: 2025/03/13 02:49:25 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t get_time_ms(void)
{
	t_time time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void precise_sleep(time_t duration)
{
	time_t start_time;

	start_time = get_time_ms();
	while (get_time_ms() - start_time < duration)
		usleep(500);
}

