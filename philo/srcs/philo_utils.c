#include "philo.h"

int	get_time(void)
{
	struct timeval	current_time;
	int	time_ms;

	if (gettimeofday(&current_time, NULL) != 0)
		return (ft_putstr_fd("Error with gettimeofday\n", 2), -1);
	time_ms = (int)(current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	return (time_ms);
}

int	ft_usleep(t_philo *philo, int time)
{
	int	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		pthread_mutex_lock(philo->dead_lock);
		if (*(philo->end))
			return (pthread_mutex_unlock(philo->dead_lock), 1);
		pthread_mutex_unlock(philo->dead_lock);
		usleep(500);
	}
	return (0);
}

void	put_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->write_lock);
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->end) == 0)
		printf("%d %d %s\n", get_time() - philo->start_time, philo->id, str);
	pthread_mutex_unlock(philo->dead_lock);
	pthread_mutex_unlock(philo->write_lock);
}
