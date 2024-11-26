#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

# define FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef struct s_philosopher
{
	int			id;
	long		last_meal_time;
	int			meals_eaten;
	struct s_table	*table;
}		t_philosopher;

typedef struct s_table
{
	int			philosopher_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meals_required;
	pthread_t	thread;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	write_lock;
	t_philosopher	*philosophers;
}		t_table;


// routine.c


// utils.c
int	ft_atoi(const char *nptr);
void cleanup(t_table *table);


#endif
