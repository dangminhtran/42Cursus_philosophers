/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:36:23 by dangtran          #+#    #+#             */
/*   Updated: 2025/03/08 14:23:17 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
    int             num_of_philos;
    int             num_times_to_eat;
    size_t			start_time;
    size_t			time_to_die;
    size_t			time_to_eat;
    size_t			time_to_sleep;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	// Pas besoin de faire de malloc, les push avec une loop
	t_philo			philos[200];
}					t_program;


// MANAGE
void	init_mutex(t_program *prog);
void	destroy_mutex(t_program *prog);
void	init_philos(t_program *prog);
int 	init_program(t_program *prog, int argc, char **argv);
void    destroy_program(t_program *prog);

// PHILO
void	print_message(size_t time, int id, char *message, t_program *prog);
void	check_death(t_philo *ph, t_program *prog);
void	check_meals(t_philo *ph, t_program *prog);
void	*philo_routine(void *philo);
void	start_threads(t_program *prog);
void	destroy_threads(t_program *prog);
void	init_threads(t_program *prog);

// PARSING
int	ft_isdigit(int c);
int	is_number(char *str);
int	check_args(int argc, char **argv);

#endif