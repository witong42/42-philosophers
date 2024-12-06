/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:50:19 by witong            #+#    #+#             */
/*   Updated: 2024/12/04 15:55:25 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t-philo	*philo;
	philo = (t_philo *)arg;
	while (1)
	{
		if (check_dead(philo) || check_all_eaten(philo))
			break;
	}
	return (arg);
}
