/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:46:31 by witong            #+#    #+#             */
/*   Updated: 2024/12/03 15:48:10 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_all_eaten(t_philo *philo)
{
	int all_full;
	int	i;

	if (philo->table->meals_required != -1)
	{
		if (philo->meals_eaten >= philo->table->meals_required && !philo->full)
		{
			pthread_mutex_lock(&philo->table->meals_lock);
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
				philo->table->running = false;
			pthread_mutex_unlock(&philo->table->meals_lock);
		}
	}
}

void	thinking(t_philo *philo)
{
		putstatus(THINK, philo);
}

void eating(t_philo *philo)
{
	if (!is_running(philo))
		return ;
	pthread_mutex_lock(philo->right_fork);
	putstatus(FORK, philo);
	if (philo->table->philo_count == 1)
	{
		usleep(philo->table->time_to_die * 1000);
		pthread_mutex_unlock(philo->right_fork);
		philo->table->running = 0;
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	putstatus(FORK, philo);
	putstatus(EAT, philo);
	philo->last_meal_time = realtime();
	philo->meals_eaten++;
	check_all_eaten(philo);
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
		putstatus(SLEEP, philo);
		usleep(philo->table->time_to_sleep * 1000);
}
