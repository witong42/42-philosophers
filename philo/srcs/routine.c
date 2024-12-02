/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:20:11 by witong            #+#    #+#             */
/*   Updated: 2024/12/02 14:54:51 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_dead(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->table->write_lock);
		if (realtime() - philo->last_meal_time >= philo->table->time_to_die)
		{
			philo->table->running = 0;
			putstatus(DEAD, philo);
			pthread_mutex_unlock(&philo->table->write_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->write_lock);
		usleep(500);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (philo->table->running)
	{
		if (philo->table->running)
			thinking(philo);
		if (philo->table->running)
			eating(philo);
		if (philo->table->running)
			sleeping(philo);
	}
	return (NULL);
}

int	create_threads(t_table *table)
{
	int	i;
	pthread_t	tid0;

	if (pthread_create(&tid0, NULL, &check_dead, &table->philo[0]) != 0)
	{
		printf("Error creating threads.\n");
		return (1);
	}
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_create(&table->threads[i], NULL, &routine, &table->philo[i]) != 0)
		{
			printf("Error creating threads.\n");
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
}
