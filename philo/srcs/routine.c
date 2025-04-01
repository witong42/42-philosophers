#include "philo.h"

static void	*handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	put_status(philo, "has taken a fork");
	ft_usleep(philo, philo->time_to_die);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int	end;

	philo = (t_philo *)arg;
	if (philo->philo_count == 1)
		return (handle_one_philo(philo));
	if (philo->id % 3 == 0)
		usleep(500);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(philo->dead_lock);
		end = *(philo->end);
		pthread_mutex_unlock(philo->dead_lock);
		if (end)
			break;
		eating(philo);
		sleeping(philo);
		thinking(philo);
		usleep(200);
	}
	return (NULL);
}
