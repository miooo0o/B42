#include "philo.h"

int	*init_time_table(t_rsc *rsc, int n_philo)
{
	int	i;
	int	id;
	int *target;

	target = ft_memalloc(sizeof(int) * n_philo);
	if (!target)
		return (NULL);
	i = -1;
	id = 0;
	while (id < n_philo)
	{
		target[++i] = id;
		id += 2;
	}
	id = 1;
	while (id < n_philo)
	{
		target[++i] = id;
		id += 2;
	}
	rsc->next = &(target[0]);
	return (target);
}

int init_rsc(void)
{
	t_rsc	*rsc;
	int		num;

	rsc = rsc_instance();
	num = rsc->n_philos;
	rsc->status = RUNNING;
	rsc->time_table = init_time_table(rsc, num);
	rsc->forks = init_mutexes(num);
	rsc->locks = init_mutexes(NUM_LOCKS);
	if (!rsc->time_table || !rsc->forks || !rsc->locks)
		return (0);
	return (1);
}
