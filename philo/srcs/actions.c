/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:46:31 by witong            #+#    #+#             */
/*   Updated: 2024/12/02 16:31:25 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_all_eaten(t_philo *philo)
{

	if (philo->table->meals_required != -1)
	{
		if (philo->meals_eaten >= philo->table->meals_required)
				philo->table->running = 0;
	}
}

void	thinking(t_philo *philo)
{
		pthread_mutex_lock(&philo->table->write_lock);
		putstatus(THINK, philo);
		pthread_mutex_unlock(&philo->table->write_lock);
}

void eating(t_philo *philo)
{
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
		pthread_mutex_lock(&philo->table->write_lock);
		putstatus(EAT, philo);
		philo->last_meal_time = realtime();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->table->write_lock);
		check_all_eaten(philo);
		usleep(philo->table->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
}

void	sleeping(t_philo *philo)
{
		pthread_mutex_lock(&philo->table->write_lock);
		putstatus(SLEEP, philo);
		pthread_mutex_unlock(&philo->table->write_lock);
		usleep(philo->table->time_to_sleep * 1000);
}
