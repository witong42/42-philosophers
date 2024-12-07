# 42-philosophers

## Table of contents
1. [Introduction](#Introduction)
2. [Allowed Functions](##Functions)
3. [Step-by-step](##Step-by-step)
	1. [Parsing](#step1)
	2. [Structures](#step2)
	3. [Initialization and Memory Allocation](#step3)
	4. [Routine](#step4)
	5. [Supervisor](#step5)
	6. [Monitor](#step6)
	7. [Memory Management](#step7)

## Introduction

So basically in philo we need to make a thread for each philosophers, each philosopher comes with a fork that cannot be duplicated or used by others at the same time.

They are sitted on a "round table" with each N philosopher between N-1 and N+1;

The trick is that each philosopher need both right and left fork at the same time to eat and if they don't eat they die.

The thing is we have to prevent them from dying, so we have to avoid data races and deadlocks.

A date race is when a thread is writing on a mutable object at the same time as another one is accessing it, it makes the data incoherent. A deadlock is when two threads seeks for the lock of each others but no one drops, both threads are therefore "blocked waiting".

For this project we need to familiarize ourselves with threads and mutex.


1. Threads

A thread is a small sequence of programmed instructions, and the threads are a subset of a process.
They are sometimes called lightweight processes.

Difference between processes (forks) and threads:
A fork is creating a new process that copies all the elements of an old one, or parent. In a fork, memory and resources are isolated.

Multithreading :
Using multiple threads is like having multiple tabs in your browser.

the p in pthreads is for POSIX standard for threads.

2. Mutex

A mutex is similar to an immutable key. It can be locked or unlocked using pthread_mutex_lock() and pthread_mutex_unlock(), but first has to be pthread_mutex_init(), and destroyed after use with pthread_mutex_destroy();

In philo we have init a mutex for each forks, and also when writing or counting meals to make sure there's no data race.

3. Data races

A race condition is when 2 or more threads are concurrently accessing a data

## Allowed Functions

gettimeofday() is a function who takes a struct called timeval as follows and fill the tv_sec and tv_usec respectively:

struct timeval {
	time_t	tv_sec;	/* seconds */
	suseconds_t	tv_usec;	* microseconds */
};

---

usleep() suspend the execution of the thread it is in in microseconds. ! Warning it's not miliseconds (ms) but microseconds, multiplying by 1000 to get ms.

---

pthread_create as its name indicate is to create a thread, it can be used in a loop to create multiple threads.
It takes 4 arguments as follows:

pthread_create(&thread_id, NULL, &routine, arg);

1st arg, is a pointer to a pthread_t variable id.
2nd arg, we put NULL to get the default attributes
3rd arg, a pointer to the function the thread will be executing
4th arg, used to pass an argument to the routine function.

---

pthread_join() is to threads the same as the wait() function for processes, it's waiting that the specified thread mentionned is terminated. It is also acting as a clean up

pthread_join(thread_id, returnval)

returnval if not NULL will return 0 on success or an error code.


## Step by step

<a name='step1'>1. Parsing</a>

Parsing args into a struct that will hold the variables.

<a name='step2'>2. Structures</a>

 Create another struct for the individual philosophers' data

<a name='step3'>3. Initialize and memory allocate</a>

 Initialize and memory allocate the data in the structures

<a name='step4'>4. Routine</a>

<a name='step5'>5. Supervisor</a>

<a name='step6'>6. Monitor</a>

<a name='step7'>7. Memory Management</a>

## Testing
valgrind --fair-sched=yes --tool=helgrind ./philo 5 800 200 200 7
https://github.com/Rz-Rz/thales_tester

