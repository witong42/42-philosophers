Parsing
	Validate Args
	Put Args in data structure
Initialization
	Initialize data structure
	Initialize Mutexes
	Initialize Forks
	Initialize Philos
Threads
	Create Threads
		Create Butler
			Check Death
			Check if enough meals
		Create Philos
			Routine
				One Philo
				Eat
					Grab Forks
					Update Meals
					Drop Forks
				Think
				Sleep
Join & Clean
	Join Threads
		Join Philos
		Join Butler
	Clean up all
		Destroy Mutexes
		Destroy Forks
		Free Philos

