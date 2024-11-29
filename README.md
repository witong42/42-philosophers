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

## Allowed Functions

gettimeofday() is a function who takes a struct called timeval as follows and fill the tv_sec and tv_usec respectively:

<code>
struct timeval {
	time_t	tv_sec;	/* seconds */
	suseconds_t	tv_usec;	* microseconds */
};
</code>

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


## Ideas / Todo

pair impair startup ?

right_fork = left_fork + 1

take both forks or none

check death thread

