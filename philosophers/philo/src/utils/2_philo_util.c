#include "philo.h"

time_t	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (ft_error_msg("gettimeofday fail"), -1);
	return ((long long)time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(time_t time)
{
	time_t	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < time)
		usleep(time / 10);
	return (0);
}
