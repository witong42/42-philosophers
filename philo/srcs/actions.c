/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:52:17 by witong            #+#    #+#             */
/*   Updated: 2025/04/07 11:02:58 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	pick_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		put_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		put_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		put_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		put_status(philo, "has taken a fork");
	}
}

void	eating(t_philo *philo)
{
	pick_forks(philo);
	pthread_mutex_lock(philo->meals_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meals_lock);
	put_status(philo, "is eating");
	ft_usleep(philo, philo->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleeping(t_philo *philo)
{
	put_status(philo, "is sleeping");
	ft_usleep(philo, philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	int	thinking;

	put_status(philo, "is thinking");
	thinking = philo->time_to_die - philo->time_to_eat - philo->time_to_sleep;
	if (thinking <= 10)
		return ;
	if (thinking > philo->time_to_eat)
		thinking = philo->time_to_eat;
	ft_usleep(philo, thinking);
}
