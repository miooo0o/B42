#include "philo.h"

int	is_running(t_rsc *rsc, t_philo *philo)
{
	pthread_mutex_lock(rsc->locks[LOCK_PROG_STATUS]);
	if (rsc->status != RUNNING)
	{
		if (rsc->status == FUNERAL)
			print_msg(philo, "died");
		pthread_mutex_unlock(rsc->locks[LOCK_PROG_STATUS]);
		return (0);
	}
	pthread_mutex_unlock(rsc->locks[LOCK_PROG_STATUS]);
	return (1);
}

int eat(t_rsc *rsc, t_philo *philo)
{
	return (0);
}

int jam(t_rsc *rsc, t_philo *philo)
{
	return (0);
}

int think(t_rsc *rsc, t_philo *philo)
{

	return (0);
}

int is_correct_id(t_rsc *rsc, t_philo *philo)
{
	int next;

	pthread_mutex_lock(rsc->locks[LOCK_TIME_TABLE]);
	next = *rsc->next;
	if (next == philo->id)
	{
		pthread_mutex_unlock(rsc->locks[LOCK_TIME_TABLE]);
		usleep(10);
		return (1);
	}
	pthread_mutex_unlock(rsc->locks[LOCK_TIME_TABLE]);
	return (0);
}

void	*routine(void *ptr)
{
	t_philo	*philo;
	t_rsc	*rsc;

	philo = (t_philo *)ptr;
	rsc = rsc_instance();
	while (is_running(rsc, philo))
	{
		if (!is_correct_id(rsc, philo))
			usleep(10);
		eat(rsc, philo);
		jam(rsc, philo);
		think(rsc, philo);
		usleep(100);
	}
	return (NULL);
}

int	philosopers(t_philo **philos)
{
	t_rsc		*rsc;
	pthread_t	checker;
	int			i;
	rsc = rsc_instance();
	if (pthread_create(&checker, NULL, \
	monitor, philos) != 0)
		return (-1);
	i = -1;
	while (++i < rsc->n_philos)
	{
		philos[i]->creation = get_time();
		philos[i]->last_meal = get_time();
		if (pthread_create(philos[i]->thread, NULL, \
	routine, philos[i]) != 0)
			return (-1); /// destroy
	}
	if (pthread_join(checker, NULL) != 0)
		return (-1); /// destroy
	i = -1;
	while (++i < rsc->n_philos)
	{
		if (pthread_join(*(philos[i]->thread), NULL) != 0)
			return (-1); /// destroy
	}
	return (0);
}