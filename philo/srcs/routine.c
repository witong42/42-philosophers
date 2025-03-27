#include "philo.h"

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	put_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	put_status(philo, "has taken a fork");

	put_status(philo, "is eating");
	philo->last_meal_time = get_time();
	usleep(philo->time_to_eat * 1000);

	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	sleeping(t_philo *philo)
{
	put_status(philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
}

static void	thinking(t_philo *philo)
{
	put_status(philo, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_count == 1)
	{

	}
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		if (philo->end)
			break;
	}
	return (NULL);
}
