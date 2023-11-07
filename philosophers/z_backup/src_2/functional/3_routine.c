#include "../../philo_2.h"

int	print_status(t_philo *philo, pthread_mutex_t *lock_print, char *str)
{
	long long	now;

	now = 0;
	check(pthread_mutex_lock(lock_print), ERROR_MUTEX_LOCK);
	now = ft_get_time() - philo->t_creation;
	printf("%lld %u %s\n", now, philo->id + 1, str);
	check(pthread_mutex_unlock(lock_print), ERROR_MUTEX_UNLOCK);
	return (now);
}


int in_order(t_philo *philo, pthread_mutex_t *fork1, \
				pthread_mutex_t *fork2, pthread_mutex_t *lock_print)
{
	t_config	*conf;

	conf = conf_instance();
	check(pthread_mutex_lock(conf->locks[LOCK_FORK]), ERROR_MUTEX_LOCK);
	print_status(philo, lock_print, "has taken a fork");
	print_status(philo, lock_print, "has taken a fork");
	check(pthread_mutex_unlock(conf->locks[LOCK_FORK]), ERROR_MUTEX_UNLOCK);
	return 1;
}

int lock_mutex(pthread_mutex_t *mutex)
{
	int result;

	result = check(pthread_mutex_lock(mutex), ERROR_MUTEX_LOCK);
	if (result != 0)
		return (-1);
	return (result);
}

int unlock_mutex(pthread_mutex_t *mutex)
{
	int result;

	result = check(pthread_mutex_unlock(mutex), ERROR_MUTEX_LOCK);
	if (result != 0)
		return (-1);
	return (result);
}

int	update_next_entry(t_config *conf)
{
	static int	i;
	int			last_index;

	if (lock_mutex(conf->locks[LOCK_NEXT]) != 0)
		return (-1);
	last_index = conf->n_philos - 1;
	conf->next = &(conf->time_table[++i]);
	if (i >= last_index)
		i = -1;
	if (unlock_mutex(conf->locks[LOCK_NEXT]) != 0)
		return (-1);
	return (1);
}

int eat(t_config *conf, t_philo *philo)
{
	long long time_to_eat;

//	printf("[ %lu ] enter to eat function\n", (unsigned long)philo->thread);

	check(pthread_mutex_lock(conf->locks[LOCK_FORK]), ERROR_MUTEX_LOCK);

	print_status(philo, conf->locks[LOCK_PRINT], "has taken a fork");
	print_status(philo, conf->locks[LOCK_PRINT], "has taken a fork");
	print_status(philo, conf->locks[LOCK_PRINT], "is eating");


	if (lock_mutex(conf->locks[LOCK_EAT]) != 0)
		return (-1);
	philo->t_last_meal = ft_get_time();
	philo->n_ate++;
	if (unlock_mutex(conf->locks[LOCK_EAT]) != 0)
		return (-1);
	if (lock_mutex(conf->locks[LOCK_TIME]) != 0)
		return (-1);
	time_to_eat = conf->time_eat + philo->t_last_meal;
	while (time_to_eat > ft_get_time())
		usleep(100);
	if (unlock_mutex(conf->locks[LOCK_TIME]) != 0)
		return (-1);

	if (lock_mutex(conf->locks[LOCK_STATUS]) != 0)
		return (-1);
	philo->status = ALIVE;
	if (unlock_mutex(conf->locks[LOCK_STATUS]) != 0)
		return (-1);

	///	@error update_next_entry
	update_next_entry(conf);

	check(pthread_mutex_unlock(conf->locks[LOCK_FORK]), ERROR_MUTEX_UNLOCK);
	return (1);
}

int jam(t_config *conf, t_philo *philo)
{
	long long	target_time;

	if (lock_mutex(conf->locks[LOCK_TIME]) != 0)
		return (-1);
	target_time = conf->time_jam + ft_get_time();
	while (ft_get_time() < target_time)
		usleep(10);
	if (unlock_mutex(conf->locks[LOCK_TIME]) != 0)
		return (-1);
	print_status(philo, conf->locks[LOCK_PRINT], "is sleeping");
	return (0);
}

int think(t_config *conf, t_philo *philo)
{
	print_status(philo, conf->locks[LOCK_PRINT], "is thinking");
	return (1);
}