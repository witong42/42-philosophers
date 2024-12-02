/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:58:50 by witong            #+#    #+#             */
/*   Updated: 2024/12/02 12:51:17 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	realtime(void)
{
	struct timeval	current_time;
	long long	time_ms;

	if (gettimeofday(&current_time, NULL) != 0)
		return (printf("Error with gettimeofday\n"), -1);
	time_ms = (current_time.tv_sec * 1000LL) + (current_time.tv_usec / 1000);
	return (time_ms);
}

void	putstatus(char *str, t_philo *philo)
{
	long long	time;

	time = realtime() - philo->table->set_time;
	if (time != -1)
		printf("%lld %d %s\n", time, philo->id, str);
}
