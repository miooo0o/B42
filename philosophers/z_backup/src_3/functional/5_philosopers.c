#include "../../philo_3.h"

int	is_running(t_rsc *rsc, t_philo *philo)
{
	pthread_mutex_lock(rsc->locks[LOCK_PROG_STATUS]);
	if (rsc->status != STATUS_RUNNING)
	{
		pthread_mutex_unlock(rsc->locks[LOCK_PROG_STATUS]);
		return (0);
	}
	pthread_mutex_unlock(rsc->locks[LOCK_PROG_STATUS]);
	return (1);
}

int update_next(t_rsc *rsc, t_philo *philo)
{
	static int	i;
	int			last_index;

	if (pthread_mutex_lock(rsc->locks[LOCK_TIME_TABLE]) != 0)
		return (-1);
	last_index = rsc->n_philos - 1;
	rsc->next = &(rsc->time_table[++i]);
	if (i >= last_index)
		i = -1;
	if (pthread_mutex_unlock(rsc->locks[LOCK_TIME_TABLE]) != 0)
		return (-1);
	return (1);
}

int eat(t_rsc *rsc, t_philo *philo)
{
	if (pthread_mutex_lock(philo->l_fork) != 0)
		return (-1);
	print_msg(philo, "has taken a fork");

	if (pthread_mutex_lock(philo->r_fork) != 0)
		return (-1);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");


	if (pthread_mutex_lock(rsc->locks[LOCK_UPDATE_N_MEAL]) != 0)
		return (-1);
	philo->n_eat++;
	philo->last_meal = get_time();
	if (pthread_mutex_unlock(rsc->locks[LOCK_UPDATE_N_MEAL]) != 0)
		return (-1);

	update_next(rsc, philo);

	ft_usleep(rsc->time_eat);
	if (pthread_mutex_unlock(philo->r_fork) != 0)
		return (-1);
	if (pthread_mutex_unlock(philo->l_fork) != 0)
		return (-1);

	return (0);
}

int jam(t_rsc *rsc, t_philo *philo)
{
	print_msg(philo, "is sleeping");
	ft_usleep(rsc->time_jam);
	return (0);
}

int think(t_rsc *rsc, t_philo *philo)
{
	print_msg(philo, "is thinking");
	return (0);
}

int scheduling(t_rsc *rsc, t_philo *philo)
{
	int next;

	pthread_mutex_lock(rsc->locks[LOCK_TIME_TABLE]);
	next = *rsc->next;
	pthread_mutex_unlock(rsc->locks[LOCK_TIME_TABLE]);
	if (next != philo->id)
		return (0);
	return (1);
}


void	*routine(void *ptr)
{
	t_philo	*philo;
	t_rsc	*rsc;

	philo = (t_philo *)ptr;
	rsc = rsc_instance();
	while (is_running(rsc, philo))
	{
		if (!scheduling(rsc, philo))
			continue ;
		if (eat(rsc, philo) == 0)
		{
			jam(rsc, philo);
			think(rsc, philo);
		}
	}
	usleep(100);
	return (NULL);
}

void	test_print_basic(void)
{
	t_rsc		*rsc;
	int 		i;

	rsc = rsc_instance();

	printf("\nprint rsc\n\n");
	printf("philos : %d\n", rsc->n_philos);
	printf("time to die : %ld\n", rsc->time_die);
	printf("time to eat : %ld\n", rsc->time_eat);
	printf("time to jam : %ld\n", rsc->time_jam);

	i = -1;
	printf("time table :");
	while (++i < rsc->n_philos) {
		printf("[%d]", rsc->time_table[i]);
	}
	printf("\nand start from : %d\n", *rsc->next);
	printf("\n");
	printf("\n\n	philosopers");
	printf("\n\n");
}

int	philosopers(t_philo **philos)
{
	t_rsc		*rsc;
	pthread_t	checker;
	int			i;
	rsc = rsc_instance();

	test_print_basic();

	if (pthread_create(&checker, NULL, \
	monitor, philos) != 0)
		return (-1);
	i = -1;
	while (++i < rsc->n_philos)
	{
		if (pthread_create(philos[i]->thread, NULL, \
	routine, philos[i]) != 0)
			return (-1); /// destroy
	}
	if (pthread_join(checker, NULL) != 0)
		return (-1); /// destroy
	i = -1;
	while (++i < rsc->n_philos)
	{
		if (pthread_join(*(philos[i]->thread), NULL) != 0)
			return (-1); /// destroy
	}
	return (0);
}