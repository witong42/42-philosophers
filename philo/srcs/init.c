#include "philo.h"

static void	init_philo(t_philo *philo, t_data *data, int i)
{
	philo->id = i + 1;
	philo->philo_count = data->philo_count;
	philo->time_to_die = data->time_to_die;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	philo->meals_required = data->meals_required;
	philo->meals_eaten = 0;
	philo->base_time = get_time();
	philo->last_meal_time = get_time();
	philo->end = &data->end;
	philo->write_lock = &data->write_lock;
	philo->meals_lock = &data->meals_lock;
	philo->dead_lock = &data->dead_lock;
	philo->left_fork = &data->forks[i];
	philo->right_fork = &data->forks[(i + 1) % data->philo_count];
}

int	init_philos(t_data *data)
{
	t_philo	*philos;
	int	i;

	i = 0;
	philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!philos)
		return (free_all(data),1);
	while (i < data->philo_count)
	{
		init_philo(&philos[i], data, i);
		i++;
	}
	data->philos = philos;
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			data->forks = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

int	init(t_data *data)
{
	data->end = 0;
	data->forks = NULL;
	data->philos = NULL;
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->meals_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (1);
	if (init_forks(data) != 0)
		return (1);
	if (init_philos(data) != 0)
		return (1);
	return (0);
}

int	create_threads(t_data *data)
{
	int	i;

	if (pthread_create(&data->monitor, NULL, &monitoring, data) != 0)
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].philo_thread, NULL,
				&routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].philo_thread, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
	return (0);
}
