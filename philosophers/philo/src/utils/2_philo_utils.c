#include "philo.h"

pthread_mutex_t	*init_mutexes(int count)
{
	int i;
	pthread_mutex_t	*target;

	target = ft_memalloc(sizeof(pthread_mutex_t) * count);
	if (target == NULL)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		if (pthread_mutex_init(target, NULL) != 0)
			return (NULL);
	}
	return (target);
}

time_t	ft_gettime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ft_error_msg("gettimeofday()"));
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
}

void	ft_usleep(time_t time)
{
	time_t	start;

	start = ft_gettime();
	while ((ft_gettime() - start) < time)
		usleep(10);
}

t_lock *lock_instance(void)
{
	static t_lock this;
	static int is_init;

	if (is_init) {
		return (&this);
	}
	pthread_mutex_init(&this.read_lock, NULL);
	pthread_mutex_init(&this.write_lock, NULL);
	is_init = TRUE;
	return (&this);
}

/// @note basic logic read/write
/// add mutex
int	write_val(int *dest, int src)
{
	t_lock *lock = lock_instance();
	pthread_mutex_lock(&lock->write_lock);
	*dest = src;
	pthread_mutex_unlock(&lock->write_lock);
	return (0);
}

int	read_val(int *target)
{
	int res;

	t_lock *lock = lock_instance();
	pthread_mutex_lock(&lock->read_lock);
	res = *target;
	pthread_mutex_unlock(&lock->read_lock);
	return (res);
}