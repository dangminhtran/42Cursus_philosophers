/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:37:12 by dangtran          #+#    #+#             */
/*   Updated: 2025/03/08 11:04:33 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// routine des philosophes
void    *philo_routine(void *var)
{
    t_philo	*ph;

    ph = (t_philo *)var;
    if (ph->id % 2 == 0)
        ft_usleep(1);
    while (!check_dead_flag(ph))
    {
        is_eating(ph);
        is_sleeping(ph);
        is_thinking(ph);
    }
    return (var);
}

// fonction pour lancer les threads
int	start_threads(t_program *prog, pthread_mutex_t *forks)
{
    pthread_t	monitor;
    int	i;

    if (pthread_create(&monitor, NULL, &check_routine, prog->philos) != 0)
		destroy_mutex("Thread creation error", prog, forks);
    i = 0;
    while (i < prog->philos[0].num_of_philos)
    {
        if (pthread_create(&prog->philos[i].thread, NULL, &philo_routine,
            &prog->philos[i]) != 0)
        destroy_mutex("Thread creation error", prog, forks);
    i++;
}
    i = 0;
    if (pthread_join(monitor, NULL) != 0)
        destroy_mutex("Thread join error", prog, forks);
    while (i < prog->philos[0].num_of_philos)
    {
        if (pthread_join(prog->philos[i].thread, NULL) != 0)
            destroy_mutex("Thread join error", prog, forks);
        i++;
    }
    return (0);
}

// fonction pour detruire les threads
void	destroy_mutex(char *str, t_program *program, pthread_mutex_t *forks)
{
    int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->dead_lock);
	while (i < program->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}