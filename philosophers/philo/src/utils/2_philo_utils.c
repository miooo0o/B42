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
		return (-1);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
}

void	ft_usleep(time_t time)
{
	time_t	start;

	start = ft_gettime();
	while ((ft_gettime() - start) < time)
		usleep(10);
}

void	print_status(t_philo *philo, char *msg)
{
	time_t	now;

}