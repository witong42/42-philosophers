/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:11:08 by witong            #+#    #+#             */
/*   Updated: 2025/04/02 18:52:13 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_atoi_safe(char *str)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		num = num * 10 + (str[i] - '0');
		if (num > INT_MAX)
			return (-1);
		i++;
	}
	return ((int)num);
}
void	free_all(t_data *data)
{
	int	i;

	if (data->write_lock_init)
		pthread_mutex_destroy(&data->write_lock);
	if (data->meals_lock_init)
		pthread_mutex_destroy(&data->meals_lock);
	if (data->dead_lock_init)
		pthread_mutex_destroy(&data->dead_lock);
	if (data->forks)
	{
		i = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}
