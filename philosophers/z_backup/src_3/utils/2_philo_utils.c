#include "../../philo_3.h"

pthread_mutex_t	**init_mutexes(int count)
{
	int i;
	pthread_mutex_t	**target;

	target = ft_memalloc(sizeof(pthread_mutex_t *) * count);
	if (target == NULL)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		target[i] = ft_memalloc(sizeof(pthread_mutex_t));
		if (target[i] == NULL)
			return (NULL);
		if (pthread_mutex_init(target[i], NULL) != 0)
			return (NULL);
	}
	return (target);
}

time_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ft_error_msg("gettimeofday()"));
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
}

int	ft_usleep(time_t time)
{
	time_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}


void	print_msg(t_philo *philo, char *msg)
{
	long long	now;
	t_rsc		*rsc;

	rsc = rsc_instance();
	now = 0;
	pthread_mutex_lock(rsc->locks[LOCK_WRITE]);
	now = get_time() - philo->creation;
	if (is_running(rsc, philo))
		printf("%lld %d %s\n", now, philo->id + 1, msg);
	pthread_mutex_unlock(rsc->locks[LOCK_WRITE]);
}