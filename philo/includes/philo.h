#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_philo
{
    int             id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    int             time_to_eat;    // Time it takes to eat (in milliseconds)
    int             time_to_sleep;  // Time it takes to sleep (in milliseconds)
    long long       last_meal_time; // Timestamp of the last meal
} t_philo;

void    put_status(t_philo *philo, char *status);
long long   get_time(void);

#endif
