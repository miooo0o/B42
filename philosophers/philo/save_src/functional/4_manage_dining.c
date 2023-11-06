#include "../../../philo.h"

int lock_and_unlock(t_errortype type)
{
	t_config	*conf;

	conf = conf_instance();
	if (check(pthread_mutex_lock(conf->locks[LOCK_START]), type) != 0)
		return (-1);
	if (check(pthread_mutex_unlock(conf->locks[LOCK_START]), type + 1) != 0)
		return (-1);
	return (0);
}

void	*lifecycle(void *target)
{
	t_config	*conf;
	t_philo		*philo;

	philo = (t_philo *)target;

	conf = conf_instance();
	lock_and_unlock(ERROR_MUTEX_LOCK);

	while (1)
	{
		check(pthread_mutex_lock(conf->locks[LOCK_START]), ERROR_MUTEX_LOCK);
		if (philo->id != *conf->next)
		{
			usleep(10);
			check(pthread_mutex_unlock(conf->locks[LOCK_START]), ERROR_MUTEX_UNLOCK);
			continue ;
		}
		else
			check(pthread_mutex_unlock(conf->locks[LOCK_START]), ERROR_MUTEX_UNLOCK);



//		printf("[ %lu ] enter to while loop\n", (unsigned long)philo->thread);
		lock_and_unlock(ERROR_MUTEX_LOCK);

		eat(conf, philo);

		lock_mutex(conf->locks[LOCK_STATUS]);
		if (philo->n_ate == conf->required_eat)
		{
			unlock_mutex(conf->locks[LOCK_STATUS]);
			break;
		}
		unlock_mutex(conf->locks[LOCK_STATUS]);
		jam(conf, philo);
		think(conf, philo);

	}
	return (0);
}


void	destroy_all(t_config *conf, t_philo **philos)
{
	int i;

	i = -1;
	while (++i < conf->n_philos)
		pthread_mutex_destroy(conf->forks[i]);
	ft_free_2d((void **)conf->forks);
	i = -1;
	while (++i < LOCKTYPE_COUNT)
		pthread_mutex_destroy(conf->locks[i]);
	ft_free_2d((void **)conf->locks);
}

void	join_threads(t_config *conf, t_philo **philos)
{
	int i;

	i = -1;
	while (++i < conf->n_philos)
		pthread_join(*(philos[i]->thread), NULL);
}


int philosophers(t_config *conf, t_philo **philos)
{
	int	i;
	i = -1;

	/// @test
//	printf("thread check in philosopers\n");
//	for (int j = -1; ++j < conf->n_philos;)
//		printf("%d: [%lu]\n", philos[j]->id, (unsigned long)philos[j]->thread);
//	printf("\n");
//

	while (++i < conf->n_philos)
	{
		if (check (pthread_create(philos[i]->thread, NULL, \
		&lifecycle, philos[i]), ERROR_THREAD_CREATE) != 0)
			return (destroy_all(conf, philos), ft_error_type(ERROR_THREAD_CREATE), 1);
	}
	join_threads(conf, philos);

	return (0);
}