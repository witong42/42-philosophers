#include "philo.h"

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
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleeping(t_philo *philo)
{
	put_status(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep, philo);
}

void	thinking(t_philo *philo)
{
	int	thinking;

	thinking = philo->time_to_die - philo->time_to_eat
		- philo->time_to_sleep - 1;
	if (thinking < 0)
		thinking = 0;
	put_status(philo, "is thinking");
	ft_usleep(thinking, philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		put_status(philo, "has taken a fork");
		ft_usleep(philo->time_to_die, philo);
		put_status(philo, "has died");
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		usleep(100);
		pthread_mutex_lock(philo->dead_lock);
		if (*(philo->end))
			break;
		pthread_mutex_unlock(philo->dead_lock);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (NULL);
}
