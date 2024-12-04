/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:20:11 by witong            #+#    #+#             */
/*   Updated: 2024/12/04 17:02:52 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_running(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead_lock);
	if (!philo->table->running)
	{
		pthread_mutex_unlock(&philo->table->dead_lock);
		return (false);
	}
	pthread_mutex_unlock(&philo->table->dead_lock);
	return (true);
}

void	*check_dead(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (!is_running(philo))
			break ;
		pthread_mutex_lock(&philo->table->meals_lock);
		if (realtime() - philo->last_meal_time >= philo->table->time_to_die)
		{
			pthread_mutex_unlock(&philo->table->meals_lock);
			putstatus(DEAD, philo);
			pthread_mutex_lock(&philo->table->dead_lock);
			usleep(100);
			philo->table->running = 0;
			pthread_mutex_unlock(&philo->table->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->meals_lock);
		usleep(100);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		check_all_eaten(philo);
		if (!is_running(philo))
			break ;
		pick_forks(philo);
		if (!is_running(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		eating(philo);
		if (!is_running(philo))
			break ;
		sleeping(philo);
		if (!is_running(philo))
			break ;
		thinking(philo);
		usleep(100);
	}
	return (NULL);
}

int	create_threads(t_table *table)
{
	int	i;

	if (pthread_create(&table->tid0, NULL, &check_dead, &table->philo[0]) != 0)
	{
		cleanup(table);
		return (1);
	}
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_create(&table->threads[i], NULL, &routine, &table->philo[i]) != 0)
		{
			cleanup(table);
			return (1);
		}
		i++;
	}
	return (0);
}

void join_threads(t_table *table)
{
	int i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_join(table->threads[i], NULL);
		i++;
	}
	pthread_join(table->tid0, NULL);
}
