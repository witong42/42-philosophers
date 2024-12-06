/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:46:31 by witong            #+#    #+#             */
/*   Updated: 2024/12/04 22:11:40 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			{
				pthread_mutex_lock(&philo->table->dead_lock);
				philo->table->running = false;
				pthread_mutex_unlock(&philo->table->dead_lock);
			}
		}
		pthread_mutex_unlock(&philo->table->meals_lock);
	}
}

void	thinking(t_philo *philo)
{
		if (!is_running(philo))
			return ;
		putstatus(THINK, philo);
}
void	philo_one(t_philo *philo)
{
	if (philo->table->philo_count == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		putstatus(FORK, philo);
		usleep(philo->table->time_to_die * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(&philo->table->dead_lock);
		philo->table->running = false;
		pthread_mutex_unlock(&philo->table->dead_lock);
		return ;
	}
}

void	pick_forks(t_philo *philo)
{
	if (!is_running(philo))
		return ;
	if (philo->right_fork < philo->left_fork)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	putstatus(FORK, philo);
	putstatus(FORK, philo);
}

void	eating(t_philo *philo)
{
	if (!is_running(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	putstatus(EAT, philo);
	pthread_mutex_lock(&philo->table->meals_lock);
	philo->last_meal_time = realtime();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meals_lock);
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
		if (!is_running(philo))
			return ;
		putstatus(SLEEP, philo);
		usleep(philo->table->time_to_sleep * 1000);
}
