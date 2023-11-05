#include "philo.h"

int lock_and_unlock(pthread_mutex_t *mutex, t_locktype type)
{
	if (check(pthread_mutex_lock(mutex), type) != 0 ||
		check(pthread_mutex_unlock(mutex), type + 1) != 0)
		return (-1);
	return (0);
}

void	*lifecycle(void *philo)
{
	t_config	*conf;

//	lock_and_unlock(((t_philo *)philo)->start_flag, LOCK_START);
	conf = conf_instance();
	while (1)
	{
		eating(conf, philo);
		ft_usleep(10);
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


int philosophers(t_config *conf, t_philo **philos)
{
	int	i;

	i = -1;
	while (++i < conf->n_philos)
	{
		if (check (pthread_create(philos[i]->thread, NULL, \
		&lifecycle, philos[i]), THREAD_CREATE) != 0)
			return (destroy_all(conf, philos), ft_error_type(THREAD_CREATE), 1);
	}
	return (0);
}