#include "philo.h"

static int check_death(t_data *data)
{
	int		i;
	long	last_meal;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->meals_lock);
		last_meal = get_time() - data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->meals_lock);
		if (last_meal > data->philos[i].time_to_die)
		{
			put_status(&data->philos[i], "died");
			pthread_mutex_lock(&data->dead_lock);
			data->end = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static int check_meals(t_data *data)
{
	int	i;
	int	all_eaten;

	if (data->meals_required == -1)
		return (0);
	all_eaten = 0;
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->meals_lock);
		if (data->philos[i].meals_eaten == data->meals_required)
			all_eaten++;
		pthread_mutex_unlock(&data->meals_lock);
		i++;
	}
	if (all_eaten == data->philo_count)
	{
		pthread_mutex_lock(&data->dead_lock);
		data->end = 1;
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	usleep(1000);
	while (1)
	{
		if (check_death(data) || check_meals(data))
			break ;
		usleep(200);
	}
	return (NULL);
}
