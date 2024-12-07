/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:21:53 by witong            #+#    #+#             */
/*   Updated: 2024/12/07 11:49:17 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_table(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		return (1);
	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].id = i;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = realtime();
		table->philos[i].full = false;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->philo_count];
		table->philos[i].table = table;
		i++;
	}
	table->threads = malloc(sizeof(pthread_t) * table->philo_count);
	if (!table->threads)
	{
		free(table->philos);
		return (1);
	}
	return (0);
}

int init_forks(t_table *table)
{
	int i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (!table->forks)
		return (cleanup(table), 1);
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(table->forks[i]));
			cleanup(table);
			return (1);
		}
		i++;
	}
	return (0);
}

int init(t_table *table)
{
	if (init_forks(table) != 0)
	{
		cleanup(table);
		return (1);
	}
	if (init_table(table) != 0)
		return (cleanup(table), 1);
	if (pthread_mutex_init(&(table->write_lock), NULL) != 0)
	{
		cleanup(table);
		return (1);
	}
	if (pthread_mutex_init(&(table->meals_lock), NULL) != 0)
	{
		cleanup(table);
		return (1);
	}
	if (pthread_mutex_init(&(table->dead_lock), NULL) != 0)
	{
		cleanup(table);
		return (1);
	}
	return (0);
}
