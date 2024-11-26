/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:20:11 by witong            #+#    #+#             */
/*   Updated: 2024/11/26 20:38:35 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (philo->table->running)
    {
        pick_forks(philo);
        eat(philo);
        drop_forks(philo);
        sleep_think(philo);
        if (realtime() - philo->last_meal_time > philo->table->time_to_die)
        {
            putstatus(DEAD, philo);
            philo->table->running = 0;
            break;
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
            printf("Error creating thread for philosopher %d\n", i + 1);
            return 1;
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
