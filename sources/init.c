#include "philo.h"

// initialiser avec les arguments
void    init_args(t_philo *philo, char **argv)
{
    philo->time_to_die = ft_atoi(argv[2]);
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_sleep = ft_atoi(argv[4]);
    philo->num_of_philos = ft_atoi(argv[1]);
    if (argv[5])
        philo->nb_meals_to_eat = ft_atoi(argv[5]);
    else
        philo->nb_meals_to_eat = -1;

}

// Initialiser les fourchettes
void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

// initialiser les philosophes
void	init_philos(t_philo *philos, t_program *prog, pthread_mutex_t *forks, char **argv)
{
    int	i;

    i = 0;
    while (i < ft_atoi(argv[1]))
    {
        philos[i].id = i + 1;
        philos[i].eating = 0;
        philos[i].meals_eaten = 0;
        init_args(&philos[i], argv);
        philos[i].start_time = get_time();
        philos[i].last_meal = get_time();
        philos[i].write_lock = &prog->write_lock;
		philos[i].dead_lock = &prog->dead_lock;
		philos[i].meal_lock = &prog->meal_lock;
        philos[i].dead = &prog->dead_flag;
        philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].num_of_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
        i++;
    }
}

// Initialiser le programme
void	init_program(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}