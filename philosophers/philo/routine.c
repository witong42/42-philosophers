/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:20:11 by witong            #+#    #+#             */
/*   Updated: 2024/11/26 13:45:39 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine(t_table table)
{
	int	i;
	i = 0;
	while (i < table->philosopher_count)
		pthread_create()
	monitoring()
	join_threads()

}

// Step 1: Initialize all necessary mutexes
pthread_mutex_t forks[philosopher_count];
for (int i = 0; i < philosopher_count; i++) {
    pthread_mutex_init(&forks[i], NULL);
}

// Step 2: Manage input (e.g., set up philosopher data)

// Step 3: Create philosopher threads
pthread_t threads[philosopher_count];
for (int i = 0; i < philosopher_count; i++) {
    pthread_create(&threads[i], NULL, philosopher_routine, &philosophers[i]);
}

// Step 4: Within each thread
void* philosopher_routine(void* arg) {
    // Lock mutex before accessing a shared resource
    pthread_mutex_lock(&forks[left_fork]);
    pthread_mutex_lock(&forks[right_fork]);

    // Critical section: eating
    // Unlock mutex after done eating
    pthread_mutex_unlock(&forks[right_fork]);
    pthread_mutex_unlock(&forks[left_fork]);

    // Non-critical section: thinking or sleeping
}

// Step 5: Join threads to wait for all of them to finish
for (int i = 0; i < philosopher_count; i++) {
    pthread_join(threads[i], NULL);
}

// Step 6: Output (e.g., summary of philosopher states)
