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

/// @note Converts microseconds to milliseconds.
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

void	ft_print(t_philo *philo, t_steps step)
{
	t_ll	current;
	t_rsc	*rsc;

	rsc = rsc_instance();

	pthread_mutex_lock(&rsc->arr_m_status[philo->id]);
	pthread_mutex_lock(&rsc->print);
	current = ft_gettime() - philo->creation_time;
	if (step == FORK && philo->is_alive)
		printf("%*lld %d has taken a fork\n", ALIGN, current, philo->id);
	if (step == EAT && philo->is_alive)
		printf("%*lld %d is eating\n", ALIGN, current, philo->id);
	if (step == SLEEP && philo->is_alive)
		printf("%*lld %d is sleeping\n", ALIGN, current, philo->id);
	if (step == THINK && philo->is_alive)
		printf("%*lld %d is thinking\n", ALIGN, current, philo->id);
	if (step == DIE && philo->is_alive)
		printf("%*lld %d has died\\n", ALIGN, current, philo->id);
	pthread_mutex_lock(&rsc->print);
	pthread_mutex_unlock(&rsc->arr_m_status[philo->id]);
}

t_ll	to_microsec(t_ll millisec)
{
	return (millisec * 1000);
}

t_ll	to_millisec(t_ll microsec)
{
	return (microsec / 1000);
}