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

# define PHILO_MAX 200

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
	int				nb_meals_to_eat;
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
	t_philo			*philos;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
}					t_program;

// INIT
void    init_args(t_philo *philo, char **argv);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_philos(t_philo *philos, t_program *prog, pthread_mutex_t *forks, char **argv);
void	init_program(t_program *program, t_philo *philos);

// CHECK
int	is_dead(t_philo *philo, size_t time_to_die);
int	check_death(t_philo *philos);
int	check_meals(t_philo *philos);
void	*check_routine(void *pointer);
int	check_dead_flag(t_philo *philo);

// ROUTINE
void	print_message(char *message, t_philo *philo, int id);
void    is_thinking(t_philo *philo);
void    is_sleeping(t_philo *philo);
void	is_eating(t_philo *philo);

// PHILO
void    *philo_routine(void *var);
int	start_threads(t_program *prog, pthread_mutex_t *forks);
void	destroy_mutex(char *str, t_program *program, pthread_mutex_t *forks);

// PARSING
int	is_number(char *str);
int	check_arg(char *arg);
int	check_args(char **argv);

// LIBFT
int	ft_isdigit(int c);
int	ft_strlen(char *str);
int	ft_atoi(char *str);
int	ft_usleep(size_t milliseconds);
size_t	get_time(void);

#endif