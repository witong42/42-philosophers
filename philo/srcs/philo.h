#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

# define FORK "has taken a fork"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define DEAD "died"

typedef struct s_philo
{
	int				id;
	long			meals_eaten;
	bool			full;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
}		t_philo;

typedef struct s_table
{
	long			philo_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_required;
	long		set_time;
	bool		running;
	pthread_t	*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	struct s_philo	*philo;
}		t_table;

// init.c
int init(t_table *table);

// routine.c
void *routine(void *arg);
int	create_threads(t_table *table);
void join_threads(t_table *table);

// actions.c
void	pick_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

// utils_ft.c
long	ft_atol(const char *nptr);
void	cleanup(t_table *table);

// utils_philo.c
long	realtime(void);
void	putstatus(char *str, t_philo *philo);

#endif
