#include "philo.h"

// fonction pour afficher un message
void	print_message(char *message, t_philo *philo, int id)
{
    size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->start_time;
	if (!check_dead_flag(philo))
		printf("%zu %d %s\n", time, id, message);
	pthread_mutex_unlock(philo->write_lock);
}

// Mini fonctions
void    is_thinking(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

void    is_sleeping(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

// Fonction pour manger
void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a right fork", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a left fork", philo, philo->id);
	philo->eating = 1;
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	print_message("has eaten - EXTRA", philo, philo->id);
	printf("Number of meals eaten: %d by philo nb %d\n", philo->meals_eaten, philo->id);
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}