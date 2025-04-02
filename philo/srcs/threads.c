/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:54:03 by witong            #+#    #+#             */
/*   Updated: 2025/04/01 23:05:04 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	join_threads(t_data *data)
{
	int	i;

	pthread_join(data->monitor, NULL);
	i = 0;
	while (i < data->threads_count)
	{
		pthread_join(data->philos[i].philo_thread, NULL);
		i++;
	}
}

int	create_threads(t_data *data)
{
	int	i;

	if (pthread_create(&data->monitor, NULL, &monitoring, data) != 0)
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].philo_thread, NULL,
				&routine, &data->philos[i]) != 0)
		{
			pthread_mutex_lock(&data->dead_lock);
			data->end = 1;
			pthread_mutex_unlock(&data->dead_lock);
			break ;
		}
		data->threads_count++;
		i++;
	}
	join_threads(data);
	if (data->threads_count < data->philo_count)
		return (1);
	return (0);
}

