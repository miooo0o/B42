#include "philo.h"

int	print_status(t_philo *philo, pthread_mutex_t *lock_print, char *str)
{
	long long	now;

	now = 0;
	check(pthread_mutex_lock(lock_print), MUTEX_LOCK);
	now = ft_get_time() - philo->t_creation;
	printf("%lld %u %s\n", now, philo->id + 1, str);
	check(pthread_mutex_unlock(lock_print), MUTEX_UNLOCK);
	return (now);
}


int in_order(t_philo *philo, pthread_mutex_t *fork1, \
				pthread_mutex_t *fork2, pthread_mutex_t *lock_print)
{
	check(pthread_mutex_lock(fork1), MUTEX_LOCK);
	print_status(philo, lock_print, "has taken a fork");
	check(pthread_mutex_lock(fork2), MUTEX_LOCK);
	print_status(philo, lock_print, "has taken a fork");
	return 1;
}

int lock_mutex(pthread_mutex_t *mutex)
{
	int result;

	result = check(pthread_mutex_lock(mutex), MUTEX_LOCK);
	if (result != 0)
		return (-1);
	return (result);
}

int unlock_mutex(pthread_mutex_t *mutex)
{
	int result;

	result = check(pthread_mutex_unlock(mutex), MUTEX_LOCK);
	if (result != 0)
		return (-1);
	return (result);
}

int grab_forks(t_philo *philo, pthread_mutex_t *lock_print)
{
	if (philo->num_type == NUM_EVEN)
		return (in_order(philo, philo->l_fork, philo->r_fork, lock_print));
	else
		return (in_order(philo, philo->r_fork, philo->l_fork, lock_print));
}

int release_fork(t_philo *philo)
{
	check(pthread_mutex_unlock(philo->l_fork), MUTEX_LOCK);
	check(pthread_mutex_unlock(philo->r_fork), MUTEX_LOCK);
	return (1);
}

int eating(t_config *conf, t_philo *philo)
{
	/// FIXME : mutex error : 괜히 작은 함수들 만들지 말고 풀어두는게 나을지도.
//	grab_forks(philo, conf->locks[LOCK_PRINT]);
//	print_status(philo, conf->locks[LOCK_PRINT], "is eating");

	if (lock_mutex(conf->locks[LOCK_EAT]) != 0)
		return (-1);
	philo->t_last_meal = ft_get_time();
	philo->n_ate++;
	if (unlock_mutex(conf->locks[LOCK_EAT]) != 0)
		return (-1);
	if (lock_mutex(conf->locks[LOCK_STATUS]) != 0)
		return (-1);
	philo->status = ALIVE;
	if (unlock_mutex(conf->locks[LOCK_STATUS]) != 0)
		return (-1);
//	release_fork(philo);
}

int sleeping(t_config *conf, t_philo **philos)
{

}

int jaming(t_config *conf, t_philo **philos)
{

}