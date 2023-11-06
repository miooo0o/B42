#include "../../../philo.h"

long long	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (ft_error_msg("gettimeofday fail"), -1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}