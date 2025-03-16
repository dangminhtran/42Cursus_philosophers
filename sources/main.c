/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:37:15 by dangtran          #+#    #+#             */
/*   Updated: 2025/03/08 14:24:33 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_program	prog;
    t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

    if (argc < 5 || argc > 6)
    {
        printf("Error: wrong number of arguments\n");
        return (1);
    }
    if (check_args(argv) == 1)
        return (1);
    init_program(&prog, philos);
    init_forks(forks, ft_atoi(argv[1]));
	init_philos(philos, &prog, forks, argv);
	start_threads(&prog, forks);
	destroy_mutex(NULL, &prog, forks);
    return (0);
}