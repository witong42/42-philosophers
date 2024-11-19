/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:21:53 by witong            #+#    #+#             */
/*   Updated: 2024/11/19 16:22:07 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void cleanup(t_table *table)
{
	int i;

	if (table->forks)
	{
		i = 0;
		while (i < table->philosopher_count)
			pthread_mutex_destroy(&(table->forks[i++]));
		free(table->forks);
	}
	if (table->philosophers)
		free(table->philosophers);
	pthread_mutex_destroy(&(table->write_lock));
}

int init_philos(t_table *table)
{
	int	i;

	table->philosophers = malloc(sizeof(t_philosopher) * table->philosopher_count);
	if (!table->philosophers)
		return (1);
	i = 0;
	while (i < table->philosopher_count)
	{
		table->philosophers[i].id = i;
		table->philosophers[i].meals_eaten = 0;
		table->philosophers[i].last_meal_time = 0;
		table->philosophers[i].table = table;
		i++;
	}
	return (0);
}

int init_forks(t_table *table)
{
	int i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->philosopher_count);
	if (!table->forks)
		return (1);
	i = 0;
	while (i < table->philosopher_count)
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

int main(void) {
    t_table table;

    // Set table parameters
    table.philosopher_count = 5;
    table.time_to_die = 800;
    table.time_to_eat = 200;
    table.time_to_sleep = 200;
    table.meals_required = 3;

    // Initialize the table and its philosophers
    int result = init(&table);

    if (result == 0) {
        printf("Initialization successful.\n");
    } else {
        printf("Initialization failed with error code: %d\n", result);
        return result;
    }

    // Print the initialized variables
    printf("Philosopher Count: %d\n", table.philosopher_count);
    printf("Time to Die: %d\n", table.time_to_die);
    printf("Time to Eat: %d\n", table.time_to_eat);
    printf("Time to Sleep: %d\n", table.time_to_sleep);
    printf("Meals Required: %d\n", table.meals_required);

    for (int i = 0; i < table.philosopher_count; i++) {
        printf("Philosopher %d: Meals Eaten: %d, Last Meal Time: %ld\n",
               table.philosophers[i].id,
               table.philosophers[i].meals_eaten,
               table.philosophers[i].last_meal_time);
    }

    // Clean up resources
    cleanup(&table);

    return 0;
}
