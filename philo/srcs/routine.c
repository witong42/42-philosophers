/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:53:05 by witong            #+#    #+#             */
/*   Updated: 2025/04/02 20:08:18 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	put_status(philo, "has taken a fork");
	ft_usleep(philo, philo->time_to_die);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		end;

	philo = (t_philo *)arg;
	if (philo->philo_count == 1)
		return (handle_one_philo(philo));
	while (1)
	{
		pthread_mutex_lock(philo->dead_lock);
		end = *(philo->end);
		pthread_mutex_unlock(philo->dead_lock);
		if (end)
			break ;
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
