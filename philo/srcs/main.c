/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:10:53 by witong            #+#    #+#             */
/*   Updated: 2025/04/01 22:52:42 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	parsing(t_data *data, char **av)
{
	data->philo_count = ft_atoi_safe(av[1]);
	if (data->philo_count <= 0)
		return (1);
	data->time_to_die = ft_atoi_safe(av[2]);
	if (data->time_to_die < 0)
		return (1);
	data->time_to_eat = ft_atoi_safe(av[3]);
	if (data->time_to_eat < 0)
		return (1);
	data->time_to_sleep = ft_atoi_safe(av[4]);
	if (data->time_to_sleep < 0)
		return (1);
	if (av[5])
	{
		data->meals_required = ft_atoi_safe(av[5]);
		if (data->meals_required <= 0)
			return (1);
	}
	else
		data->meals_required = -1;
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (ft_putstr_fd("Invalid number of args.\n", 2), 1);
	if (parsing(&data, av) != 0)
		return (ft_putstr_fd("Parsing error.\n", 2), 1);
	if (init(&data) != 0)
		return (free_all(&data), ft_putstr_fd("Initialization error.\n", 2), 1);
	if (create_threads(&data) != 0)
		return (free_all(&data), ft_putstr_fd("Threads creation error.\n", 2), 1);
	free_all(&data);
	return (0);
}
