#include "philo.h"

t_exit	init_arr_m_mutex(int count, t_mutex **target)
{
	int		i;
	t_mutex	*this;

	this = NULL;
	this = ft_memalloc(sizeof(t_mutex) * count);
	if (this == NULL)
		return (MEM_ERROR);
	i = -1;
	while (++i < count)
	{
		if (pthread_mutex_init(&this[i], NULL) != 0)
			return (free(this), INIT_ERROR);
	}
	*target = this;
	return (SUCCESS);
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