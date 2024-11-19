// atoi

void cleanup(t_table *table)
{
	int i;

	if (table->forks)
	{
		i = 0;
		while (i < table->philosopher_count)
			pthread_mutex_destroy(&(table->forks[i++]));
		free(table->forks);
	}
	if (table->philosophers)
		free(table->philosophers);
	pthread_mutex_destroy(&(table->write_lock));
}
