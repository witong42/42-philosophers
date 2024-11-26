/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:21:53 by witong            #+#    #+#             */
/*   Updated: 2024/11/26 14:54:12 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_philos(t_table *table)
{
	int	i;

	table->philo = malloc(sizeof(t_philosopher) * table->philosopher_count);
	if (!table->philo)
		return (1);
	i = 0;
	while (i < table->philosopher_count)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meals_eaten = 0;
		table->philo[i].last_meal_time = 0;
		table->philo[i].table = table;
		i++;
	}
	return (0);
}

int init_forks(t_table *table)
{
	int i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (!table->forks)
		return (1);
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL) != 0) {
			while (--i >= 0)
				pthread_mutex_destroy(&(table->forks[i]));
			free(table->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

int init(t_table *table)
{
	if (init_philos(table) != 0)
		return 1;
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
