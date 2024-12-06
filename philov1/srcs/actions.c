/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:46:31 by witong            #+#    #+#             */
/*   Updated: 2024/12/06 13:09:11 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
		if (!is_running(philo))
			return ;
		putstatus(THINK, philo);
}

void	pick_forks(t_philo *philo)
{
	if (!is_running(philo))
		return ;
	if (philo->id % 2 == 0)
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
