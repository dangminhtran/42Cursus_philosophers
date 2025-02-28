/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:37:12 by dangtran          #+#    #+#             */
/*   Updated: 2025/02/28 19:15:30 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// fonction pour afficher un message
void	print_message(size_t time, int id, char *message, t_program *prog)
{
    pthread_mutex_lock(&prog->write_lock);
    printf("%zu %d %s\n", time - prog->start_time, id, message);
    pthread_mutex_unlock(&prog->write_lock);
}

// fonction pour verifier si un philosophe est mort
void	check_death(t_philo *ph, t_program *prog)
{
    if (get_time() - ph->last_meal > prog->time_to_die)
    {
        pthread_mutex_lock(ph->dead_lock);
        *ph->dead = 1;
        pthread_mutex_unlock(ph->dead_lock);
        print_message(get_time(), ph->id, "died", prog);
    }
}

// fonction pour verifier si un philosophe a mange assez de fois
void	check_meals(t_philo *ph, t_program *prog)
{
    if (ph->num_times_to_eat != -1 && ph->meals_eaten >= ph->num_times_to_eat)
    {
        pthread_mutex_lock(ph->dead_lock);
        *ph->dead = 1;
        pthread_mutex_unlock(ph->dead_lock);
    }
}

// fonction pour obtenir le temps
size_t	get_time(void)
{
    struct timeval	time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

// fonction pour obtenir le temps actuel
size_t	get_time_now(t_program *prog)
{
    return (get_time() - prog->start_time);
}

// routine des philosophes
void    *philo_routine(void *arg)
{
    t_philo	*ph;
    t_program	*prog;

    ph = (t_philo *)arg;
    prog = (t_program *)ph;
    while (1)
    {
        pthread_mutex_lock(ph->r_fork);
        print_message(get_time(), ph->id, "has taken a fork", prog);
        pthread_mutex_lock(ph->l_fork);
        print_message(get_time(), ph->id, "has taken a fork", prog);
        pthread_mutex_lock(ph->meal_lock);
        ph->eating = 1;
        ph->last_meal = get_time();
        print_message(get_time(), ph->id, "is eating", prog);
        pthread_mutex_unlock(ph->meal_lock);
        usleep(ph->time_to_eat * 1000);
        pthread_mutex_unlock(ph->r_fork);
        pthread_mutex_unlock(ph->l_fork);
        ph->eating = 0;
        ph->meals_eaten++;
        check_meals(ph, prog);
        print_message(get_time(), ph->id, "is sleeping", prog);
        usleep(ph->time_to_sleep * 1000);
        print_message(get_time(), ph->id, "is thinking", prog);
        check_death(ph, prog);
    }
    return (NULL);
}

// fonction pour lancer les threads
void	start_threads(t_program *prog)
{
    int	i;

    i = 0;
    while (i < prog->num_of_philos)
    {
        pthread_create(&prog->philos[i].thread, NULL, philo_routine, &prog->philos[i]);
        i++;
    }
    i = 0;
    while (i < prog->num_of_philos)
    {
        pthread_join(prog->philos[i].thread, NULL);
        i++;
    }
}

// fonction pour detruire les threads
void	destroy_threads(t_program *prog)
{
    int	i;

    i = 0;
    while (i < prog->num_of_philos)
    {
        pthread_mutex_destroy(&prog->philos[i].r_fork);
        pthread_mutex_destroy(&prog->philos[i].l_fork);
        pthread_mutex_destroy(&prog->philos[i].write_lock);
        pthread_mutex_destroy(&prog->philos[i].dead_lock);
        pthread_mutex_destroy(&prog->philos[i].meal_lock);
        i++;
    }
}

// fonction pour initialiser les threads
void	init_threads(t_program *prog)
{
    int	i;

    i = 0;
    while (i < prog->num_of_philos)
    {
        prog->philos[i].id = i + 1;
        prog->philos[i].eating = 0;
        prog->philos[i].meals_eaten = 0;
        prog->philos[i].last_meal = get_time();
        prog->philos[i].time_to_die = prog->time_to_die;
        prog->philos[i].time_to_eat = prog->time_to_eat;
        prog->philos[i].time_to_sleep = prog->time_to_sleep;
        prog->philos[i].start_time = prog->start_time;
        prog->philos[i].num_of_philos = prog->num_of_philos;
        prog->philos[i].num_times_to_eat = prog->num_times_to_eat;
        prog->philos[i].dead = &prog->dead_flag;
        prog->philos[i].r_fork = &prog->philos[(i + 1) % prog->num_of_philos].l_fork;
        prog->philos[i].l_fork = &prog->philos[i].r_fork;
        prog->philos[i].write_lock = &prog->write_lock;
        prog->philos[i].dead_lock = &prog->dead_lock;
        prog->philos[i].meal_lock = &prog->meal_lock;
        pthread_mutex_init(&prog->philos[i].r_fork, NULL);
        pthread_mutex_init(&prog->philos[i].l_fork, NULL);
        pthread_mutex_init(&prog->philos[i].write_lock, NULL);
        pthread_mutex_init(&prog->philos[i].dead_lock, NULL);
        pthread_mutex_init(&prog->philos[i].meal_lock, NULL);
        i++;
    }
}


