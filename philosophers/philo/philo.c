/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:38:40 by witong            #+#    #+#             */
/*   Updated: 2024/11/19 15:58:31 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init(t_table *table)
{
	int	i;

	table->philosophers = malloc(sizeof(t_philosopher) * table->philosopher_count);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philosopher_count);
	if (!table->philosophers || !table->forks)
		return 1;
	i = 0;
	while (i < table->philosopher_count)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL) != 0)
			return 1;
		table->philosophers[i].id = i;
		table->philosophers[i].meals_eaten = 0;
		table->philosophers[i].last_meal_time = 0;
		table->philosophers[i].table = table;
		i++;
	}
	if (pthread_mutex_init(&(table->write_lock), NULL) != 0)
		return 1;

	return 0;
}

int parsing(t_table *table, char **av)
{
	table->philosopher_count = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (table->philosopher_count <= 0 || table->time_to_die <= 0
			|| table->time_to_eat <= 0 || table->time_to_sleep <= 0)
		return (1);
	if (av[5])
		table->meals_required = ft_atoi(av[5]);
	else
		table->meals_required = -1;
	return (0);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		return (1);
	if (parsing(&table, av) != 0)
		return (1);
	if (init(&table) != 0)
		return (1);
	if (routine(&table) != 0)
		return (1);
	cleanup(&table);
	return (0);
}
