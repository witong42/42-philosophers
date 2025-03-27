/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:09:15 by witong            #+#    #+#             */
/*   Updated: 2025/03/26 01:20:26 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_running(t_philo *philo)
{
	bool	running;
	
	pthread_mutex_lock(&philo->table->dead_lock);
	running = philo->table->running;
	pthread_mutex_unlock(&philo->table->dead_lock);
	return (running);
}

void	end_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead_lock);
	philo->table->running = false;
	pthread_mutex_unlock(&philo->table->dead_lock);
}

void	*check_dead(void *arg)
{
	t_philo *philo;
	int	i;

	philo = (t_philo *)arg;
	while (is_running(philo))
    {
		i = 0;
		while (i < philo->table->philo_count)
		{
			pthread_mutex_lock(&philo->table->meals_lock);
			if (realtime() - philo->table->philo[i].last_meal_time > philo->table->time_to_die)
			{
				pthread_mutex_unlock(&philo->table->meals_lock);
				putstatus(DEAD, philo);
				end_simulation(philo);
				return (NULL) ;
			}
			pthread_mutex_unlock(&philo->table->meals_lock);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

void	check_all_eaten(t_philo *philo)
{
	int all_full;
	int	i;

	if (philo->table->meals_required != -1)
	{
		pthread_mutex_lock(&philo->table->meals_lock);
		if (philo->meals_eaten >= philo->table->meals_required && !philo->full)
		{
			philo->full = true;
			all_full = 1;
			i = 0;
			while (i < philo->table->philo_count)
			{
				if (!philo->table->philo[i].full)
				{
					all_full = 0;
					break ;
				}
				i++;
			}
			if (all_full)
				end_simulation(philo);
		}
		pthread_mutex_unlock(&philo->table->meals_lock);
	}
}
