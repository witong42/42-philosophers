#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

# define FORK "has taken a fork"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define DEAD "died"

typedef struct s_philo
{
	int				id;
	long			last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	 left_fork;
	pthread_mutex_t	 right_fork;
	struct s_table	*table;
}		t_philo;

typedef struct s_table
{
	int			philo_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meals_required;
	pthread_t	thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}		t_table;


// routine.c


// utils.c
int	ft_atoi(const char *nptr);
void cleanup(t_table *table);


#endif
