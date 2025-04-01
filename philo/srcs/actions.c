#include "philo.h"

static void	pick_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		put_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		put_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		put_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		put_status(philo, "has taken a fork");
	}
}

void	eating(t_philo *philo)
{
	pick_forks(philo);
	put_status(philo, "is eating");
	pthread_mutex_lock(philo->meals_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meals_lock);
	ft_usleep(philo, philo->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleeping(t_philo *philo)
{
	put_status(philo, "is sleeping");
	ft_usleep(philo, philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	put_status(philo, "is thinking");
	ft_usleep(philo, 0);
}
