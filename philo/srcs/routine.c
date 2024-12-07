/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:20:11 by witong            #+#    #+#             */
/*   Updated: 2024/12/07 12:11:46 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->table->philo_count == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		putstatus(FORK, philo);
		usleep(philo->table->time_to_die * 1000);
		pthread_mutex_unlock(philo->right_fork);
		return (NULL);
	}
	while (is_running(philo->table))
	{
		check_all_eaten(philo);
		if (!is_running(philo->table))
			return (NULL);
		pick_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
		usleep(100);
	}
	return (NULL);
}

int	create_threads(t_table *table)
{
	int	i;

	table->running = true;
	table->set_time = realtime();
	if (pthread_create(&table->tid0, NULL, &check_dead, table) != 0)
	{
		cleanup(table);
		return (1);
	}
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_create(&table->threads[i], NULL, &routine, &table->philos[i]) != 0)
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
