/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:38:40 by witong            #+#    #+#             */
/*   Updated: 2024/11/30 12:49:01 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int parsing(t_table *table, char **av)
{
	table->set_time = realtime();
	table->philo_count = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (table->philo_count <= 0 || table->time_to_die <= 0
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
	if (create_threads(&table) != 0)
		return (1);
	join_threads(&table);
	cleanup(&table);
	return (0);
}
