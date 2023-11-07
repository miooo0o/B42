#include "../../philo_2.h"

t_numbertype determine_numtype(int num)
{
	if (ft_iseven(num))
		return (NUM_EVEN);
	return (NUM_ODD);
}

int	rightfork(int target_philo, int total_philos)
{
	int	res;

	res = 0;
	res = (target_philo + 1) % total_philos;
	return (res);
}

t_philo	*init_per_philo(t_config *conf, int id, pthread_mutex_t *r_fork, pthread_mutex_t *l_fort )
{
	t_philo	*each;

	each = ft_memalloc(sizeof(pthread_t));
	if (!each)
		return (NULL);
	each->thread = ft_memalloc(sizeof(pthread_t *));
	if (!each->thread)
		return (free(each), NULL);
	each->id = id;
	each->num_type = determine_numtype(id);
	each->n_ate = 0;
	each->t_creation = ft_get_time();
	each->t_last_meal = ft_get_time();
	each->r_fork = r_fork;
	each->l_fork = l_fort;
	each->start_flag = conf->locks[LOCK_START];
	each->status = NONE;
	return (each);
}


t_philo	**init_philos(t_config *conf)
{
	t_philo			**philos;

	philos = NULL;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				i;

	philos = (t_philo **)ft_memalloc(sizeof(t_philo *) * conf->n_philos);
	i = -1;
	while (++i < conf->n_philos)
	{
		r_fork = conf->forks[rightfork(i, conf->n_philos)];
		l_fork = conf->forks[i];
		philos[i] = init_per_philo(conf, i, r_fork, l_fork);
		if (!philos[i])
			return (ft_free_till_index((void *)philos, i));
	}
	return (philos);
}
