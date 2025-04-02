/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:23:37 by witong            #+#    #+#             */
/*   Updated: 2025/04/02 13:35:15 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	pthread_t		philo_thread;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				meals_eaten;
	int				last_meal_time;
	int				base_time;
	int				*end;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t *meals_lock;
	pthread_mutex_t *dead_lock;

}					t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				end;
	int				threads_count;
	int			base_time;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t meals_lock;
	pthread_mutex_t dead_lock;
	t_philo			*philos;
}					t_data;



// init
int		init(t_data *data);

// threads
int	create_threads(t_data *data);

// action
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

// routine
void	*routine(void *arg);

// monitoring
void	*monitoring(void *arg);

// philo_utils
int		get_time(void);
int		ft_usleep(t_philo *philo, int time);
void	put_status(t_philo *philo, char *str);

// ft_utils
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi_safe(char *str);
void	free_all(t_data *data);


#endif
