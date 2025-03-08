/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:06:54 by dangtran          #+#    #+#             */
/*   Updated: 2025/03/08 14:22:44 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Check if the arguments are valid
 */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/**
 * @brief Check if the arguments are numbers
 */
int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Check if the arguments are valid
 */
int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
		{
			printf("Error: arguments must be numbers\n");
			return (1);
		}
		if (ft_atoi(argv[i]) < 0)
		{
			printf("Error: arguments must be positive\n");
			return (1);
		}
		if (i == 1 && ft_atoi(argv[i]) > 200)
		{
			printf("Error: number of philosophers must be less than 200\n");
			return (1);
		}
		i++;
	}
	return (0);
}
