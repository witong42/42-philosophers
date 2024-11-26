/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:20:11 by witong            #+#    #+#             */
/*   Updated: 2024/11/26 15:54:03 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	pick_forks();
	eat();
	drop_forks();
	sleep_think();
}


int	create_threads(t_table *table)
{
	pthread_t threads[table->philo_count];
	int	i;

	i = 0;
	while (i < table->philo_count)
		pthread_create(&threads[i], NULL, routine, &philos[i]);
	return (0);
}

for (int i = 0; i < philo_count; i++) {
	pthread_join(threads[i], NULL);
}

int	philo_do(t_table *table)
{
	create_threads();
	monitoring();
	join_threads();
}
