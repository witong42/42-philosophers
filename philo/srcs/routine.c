/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:20:11 by witong            #+#    #+#             */
/*   Updated: 2024/11/29 15:58:41 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
int		monitoring(t_philo	*philo)
{
	if ()
		return (1);
	return (0);
}
void	*is_dead(void *arg)
{

}
*/

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(10000);
	while (philo->table->running)
	{
		if (realtime() - philo->last_meal_time >= philo->table->time_to_die)
		{
			putstatus(DEAD, philo);
			philo->table->running = 0;
			break;
		}
		if (philo->table->running)
		{
		pick_forks(philo);
		eat(philo);
		drop_forks(philo);
		sleep_think(philo);
		}
	}
	return (NULL);
}

int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_create(&table->threads[i], NULL, routine, &table->philo[i]) != 0)
		{
			printf("Error creating threads %d\n", i + 1);
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
