/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:20:11 by witong            #+#    #+#             */
/*   Updated: 2024/12/03 16:07:13 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_running(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meals_lock);
	if (!philo->table->running)
	{
		pthread_mutex_unlock(&philo->table->meals_lock);
		return false;
	}
	pthread_mutex_unlock(&philo->table->meals_lock);
	return (true);
}

void	*check_dead(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (is_running(philo))
	{
		if (!is_running(philo))
			break ;
		if (realtime() - philo->last_meal_time >= philo->table->time_to_die)
		{
			pthread_mutex_lock(&philo->table->meals_lock);
			philo->table->running = 0;
			putstatus(DEAD, philo);
			pthread_mutex_unlock(&philo->table->meals_lock);
			break ;
		}
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
		if (!is_running(philo))
			break ;
		thinking(philo);
		if (!is_running(philo))
			break ;
		eating(philo);
		if (!is_running(philo))
			break ;
		sleeping(philo);
	}
	return (NULL);
}

int	create_threads(t_table *table)
{
	int	i;

	if (pthread_create(&table->tid0, NULL, &check_dead, &table->philo[0]) != 0)
		return (1);
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_create(&table->threads[i], NULL, &routine, &table->philo[i]) != 0)
			return (1);
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
