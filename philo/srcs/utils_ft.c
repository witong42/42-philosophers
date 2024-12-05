/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:02:34 by witong            #+#    #+#             */
/*   Updated: 2024/12/04 21:15:47 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *nptr)
{
	int	i;
	long	sign;
	long	result;

	i = 0;
	result = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	return (result * sign);
}


void cleanup(t_table *table)
{
	int i;

	if (table->forks)
	{
		i = 0;
		while (i < table->philo_count)
			pthread_mutex_destroy(&(table->forks[i++]));
		free(table->forks);
	}
	if (table->philo)
		free(table->philo);
	if (table->threads)
		free(table->threads);
	if (&(table->write_lock))
		pthread_mutex_destroy(&(table->write_lock));
	if (&(table->meals_lock))
		pthread_mutex_destroy(&(table->meals_lock));
	if (&(table->dead_lock))
		pthread_mutex_destroy(&(table->dead_lock));
}
