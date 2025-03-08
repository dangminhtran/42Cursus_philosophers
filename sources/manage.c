/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:37:09 by dangtran          #+#    #+#             */
/*   Updated: 2025/03/08 14:05:49 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// initialiser les mutex
void	init_mutex(t_program *prog)
{
    pthread_mutex_init(&prog->dead_lock, NULL);
    pthread_mutex_init(&prog->meal_lock, NULL);
    pthread_mutex_init(&prog->write_lock, NULL);
}

// fonction pour detruire les mutex
void	destroy_mutex(t_program *prog)
{
    pthread_mutex_destroy(&prog->dead_lock);
    pthread_mutex_destroy(&prog->meal_lock);
    pthread_mutex_destroy(&prog->write_lock);
}

// initialiser les philosophes
void	init_philos(t_program *prog)
{
    int	i;

    i = 0;
    while (i < prog->num_of_philos)
    {
        prog->philos[i].id = i + 1;
        prog->philos[i].eating = 0;
        prog->philos[i].meals_eaten = 0;
        prog->philos[i].last_meal = 0;
        prog->philos[i].time_to_die = 0;
        prog->philos[i].time_to_eat = 0;
        prog->philos[i].time_to_sleep = 0;
        prog->philos[i].start_time = 0;
        prog->philos[i].num_of_philos = prog->num_of_philos;
        prog->philos[i].num_times_to_eat = prog->num_times_to_eat;
        prog->philos[i].dead = &prog->dead_flag;
        prog->philos[i].r_fork = &prog->philos[(i + 1) % prog->num_of_philos].l_fork;
        prog->philos[i].l_fork = &prog->philos[i].r_fork;
        prog->philos[i].write_lock = &prog->write_lock;
        prog->philos[i].dead_lock = &prog->dead_lock;
        prog->philos[i].meal_lock = &prog->meal_lock;
        i++;
    }
}

// Initialiser le programme
int	init_program(t_program *prog, int argc, char **argv)
{
    prog->dead_flag = 0;
    prog->num_of_philos = ft_atoi(argv[1]);
    prog->num_times_to_eat = (argc == 6) ? ft_atoi(argv[5]) : -1;
    prog->start_time = get_time();
    prog->time_to_die = ft_atoi(argv[2]);
    prog->time_to_eat = ft_atoi(argv[3]);
    prog->time_to_sleep = ft_atoi(argv[4]);
    // TODO - faire une boucle avec i < num_of_philos
    prog->philos = malloc(sizeof(t_philo) * prog->num_of_philos);
    if (!prog->philos)
    {
        printf("Error: malloc failed\n");
        return (1);
    }
    return (0);
}

// fonction pour detruire le programme
void	destroy_program(t_program *prog)
{
    free(prog->philos);
    destroy_mutex(prog);
}


