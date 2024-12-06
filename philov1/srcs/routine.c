/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:20:11 by witong            #+#    #+#             */
/*   Updated: 2024/12/04 22:16:58 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_running(t_philo *philo)
{
	bool running;
	pthread_mutex_lock(&philo->table->dead_lock);
	running = philo->table->running;
	pthread_mutex_unlock(&philo->table->dead_lock);
	return (running);
}

void	*check_dead(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (is_running(philo))
	{
		pthread_mutex_lock(&philo->table->meals_lock);
		if (realtime() - philo->last_meal_time >= philo->table->time_to_die)
		{
			pthread_mutex_unlock(&philo->table->meals_lock);
			putstatus(DEAD, philo);
			pthread_mutex_lock(&philo->table->dead_lock);
			philo->table->running = false;
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
	while (is_running(philo))
	{
		check_all_eaten(philo);
		if (philo->table->philo_count == 1)
		{
			philo_one(philo);
			break;
		}
		pick_forks(philo);
		eating(philo);
		if (!is_running(philo))
			break;
		sleeping(philo);
		if (!is_running(philo))
			break;
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
