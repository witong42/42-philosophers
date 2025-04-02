/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:52:58 by witong            #+#    #+#             */
/*   Updated: 2025/04/02 12:55:56 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_time(void)
{
	struct timeval	time;
	int	time_ms;

	if (gettimeofday(&time, NULL) != 0)
		return (ft_putstr_fd("Error with gettimeofday\n", 2), -1);
	time_ms = (int)(time.tv_sec * 1000 + time.tv_usec / 1000);
	return (time_ms);
}

int	ft_usleep(t_philo *philo, int time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		pthread_mutex_lock(philo->dead_lock);
		if (*(philo->end))
			return (pthread_mutex_unlock(philo->dead_lock), 1);
		pthread_mutex_unlock(philo->dead_lock);
		usleep(500);
	}
	return (0);
}

void	put_status(t_philo *philo, char *str)
{
	int		not_dead;
	int		time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->base_time;
	pthread_mutex_lock(philo->dead_lock);
	not_dead = (*(philo->end) == 0);
	pthread_mutex_unlock(philo->dead_lock);
	if (not_dead)
		printf("%d %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->write_lock);
}
