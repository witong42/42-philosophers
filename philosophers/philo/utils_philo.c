/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:58:50 by witong            #+#    #+#             */
/*   Updated: 2024/11/26 20:16:07 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	realtime(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) != 0)
		return (printf("Error with gettimeofday\n"), -1);
	return ((current_time.tv_sec * (u_int64_t)1000) + (current_time.tv_usec / 1000));
}

void	putstatus(char *str, t_philo *philo)
{
	long	time;

	time = realtime();
	if (time != -1)
		printf("%ld %d %s\n", time, philo->id, str);
}
