/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:21:53 by witong            #+#    #+#             */
/*   Updated: 2024/11/28 11:39:29 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_table(t_table *table)
{
	int	i;

	table->philo = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philo)
		return (1);
	i = 0;
	while (i < table->philo_count)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meals_eaten = 0;
		table->philo[i].last_meal_time = realtime();
		table->philo[i].table = table;
		table->philo[i].running = 1;
		i++;
	}
	table->threads = malloc(sizeof(pthread_t) * table->philo_count);
	if (!table->threads)
		return (cleanup(table), 1);
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
			free(table->forks);
			return (1);
		}
		i++;
	}
	i = 0;
    while (i < table->philo_count)
    {
        table->philo[i].left_fork = &table->forks[i];
        table->philo[i].right_fork = &table->forks[(i + 1) % table->philo_count];
        i++;
    }
	return (0);
}

int init(t_table *table)
{
	if (init_table(table) != 0)
	{
		cleanup(table);
		return (1);
	}
	if (init_forks(table) != 0)
	{
		cleanup(table);
		return (1);
	}
	if (pthread_mutex_init(&(table->write_lock), NULL) != 0)
	{
		cleanup(table);
		return (1);
	}
	return (0);
}
