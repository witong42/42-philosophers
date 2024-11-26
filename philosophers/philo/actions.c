/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:46:31 by witong            #+#    #+#             */
/*   Updated: 2024/11/26 15:53:25 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_think(t_table *table)
{
	pthread_mutex_lock(table->write_lock);
	putstatus(SLEEP, philo);
	pthread_mutex_unlock(table->write_lock);
	usleep(philo->table->time_to_sleep * 1000)
	pthread_mutex_lock(table->write_lock);
	putstatus(THINK, philo);
	pthread_mutex_unlock(table->write_lock);

}

void	pick_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	putstatus(FORK, philo);
	pthread_mutex_lock(philo->left_fork);
	putstatus(FORK, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	eat(t_philo *philo)
{
	pick_forks(philo);
	pthread_mutex_lock(philo->table->write_lock);
	philo->meals_eaten++;
	putstatus(EAT, philo);
	pthread_mutex_unlock(philo->table->write_lock);
	usleep(philo->table->time_to_eat * 1000)
	drop_forks(philo);
}

