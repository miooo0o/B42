#include "../../philo_3.h"

int	rightfork(int target_philo, int total_philos)
{
	return ((target_philo + 1) % total_philos);
}

t_philo	*init_per_philo(int id, pthread_mutex_t *r_fork, pthread_mutex_t *l_fort )
{
	t_philo	*each;

	each = ft_memalloc(sizeof(t_philo));
	if (!each)
		return (NULL);
	each->thread = ft_memalloc(sizeof(pthread_t));
	if (!each->thread)
		return (free(each), NULL);
	each->id = id;
	each->creation = get_time();
	each->last_meal = get_time();
	each->n_eat = 0;
	each->meal_state = STATE_AWAY;
	each->r_fork = r_fork;
	each->l_fork = l_fort;
	return (each);
}

t_philo	**init_philos(t_rsc	*rsc)
{
	t_philo	**philos;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				i;

	philos = ft_memalloc(sizeof(t_philo *) * rsc->n_philos);
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < rsc->n_philos)
	{
		r_fork = rsc->forks[rightfork(i, rsc->n_philos)];
		l_fork = rsc->forks[i];
		philos[i] = init_per_philo(i, r_fork, l_fork);
		if (!philos[i])
			return (ft_free_till_index((void *)philos, i));
	}
	return (philos);
}
