/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:09:09 by gstitou           #+#    #+#             */
/*   Updated: 2025/03/21 11:17:57 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	while (is_space(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int validate_args(int ac, char **av)
{
	int i;
	long value;

	i = 1;
	while (i < ac)
	{
		if (!is_valid_number(av[i]))
			return (0);
		value = ft_atol(av[i]);
		if (i == 1  && value == 0)
			return (0);
		if (value > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long ft_atol(const char *str)
{
	int sign;
	long result;

	sign = 1;
	result = 0;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + *str - 48;
		str++;
	}
	return (result * sign);
}
