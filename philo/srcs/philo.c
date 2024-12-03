/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:38:40 by witong            #+#    #+#             */
/*   Updated: 2024/12/03 10:58:45 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int parsing(t_table *table, char **av)
{
	table->philo_count = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (table->philo_count <= 0 || table->time_to_die <= 0
			|| table->time_to_eat <= 0 || table->time_to_sleep <= 0)
		return (1);
	if (av[5])
		table->meals_required = ft_atol(av[5]);
	else
		table->meals_required = -1;
	return (0);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
	{
		printf("Invalid number of args.\n");
		return (1);
	}
	if (parsing(&table, av) != 0)
	{
		printf("Parsing error.\n");
		return (1);
	}
	if (init(&table) != 0)
	{
		printf("Initialization error.\n");
		return (1);
	}
	if (create_threads(&table) != 0)
	{
		printf("Error creating threads\n.");
		return (1);
	}
	join_threads(&table);
	cleanup(&table);
	return (0);
}
