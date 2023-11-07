#include "../../philo_3.h"

int time_to_die_reached(t_philo *philo)
{
	t_rsc	*rsc;
	rsc = rsc_instance();

	pthread_mutex_lock(rsc->locks[LOCK_MEAL_STATE]);
	if (get_time() - philo->last_meal > rsc->time_eat)
	{
		pthread_mutex_unlock(rsc->locks[LOCK_MEAL_STATE]);
		return (1);
	}
	pthread_mutex_unlock(rsc->locks[LOCK_MEAL_STATE]);
	return (0);
}

int is_funeral(t_philo **philo)
{
	int 	i;
	t_rsc	*rsc;

	rsc = rsc_instance();
	i = -1;

	while (++i < rsc->n_philos)
	{
		pthread_mutex_lock(rsc->locks[LOCK_PROG_STATUS]);
		if (time_to_die_reached(philo[i]))
		{
			rsc->status = STSTUS_FINISH;
			print_msg(philo[i], "died");
			pthread_mutex_unlock(rsc->locks[LOCK_PROG_STATUS]);
			return (1);
		}
		pthread_mutex_unlock(rsc->locks[LOCK_PROG_STATUS]);
	}
	return (0);
}

int is_all_eaten(t_philo **philo)
{
	t_rsc	*rsc;
	int		full_stomach;
	int		n_philos;
	int		i;

	rsc = rsc_instance();
	if (rsc->required_meal == SET_NONE)
		return (0);
	n_philos = rsc->n_philos;
	i = -1;
	full_stomach = 0;
	while (++i < n_philos)
	{
		pthread_mutex_lock(rsc->locks[LOCK_MEAL_STATE]);
		if (philo[i]->meal_state == STATE_FULL)
			full_stomach++;
		pthread_mutex_unlock(rsc->locks[LOCK_MEAL_STATE]);
	}
	if (full_stomach == n_philos)
	{
		pthread_mutex_lock(rsc->locks[LOCK_PROG_STATUS]);
		rsc->status = STSTUS_FINISH;
		/// @note add printf?
		pthread_mutex_unlock(rsc->locks[LOCK_PROG_STATUS]);
		return (1);
	}
	return (0);
}

void	*monitor(void *ptr)
{
	t_philo	**philos;

	philos = (t_philo **)ptr;
	t_rsc	*rsc = rsc_instance();
	while (1)
	{
		if (is_funeral(philos) || is_all_eaten(philos))
			break ;
	}
	return (NULL);
}