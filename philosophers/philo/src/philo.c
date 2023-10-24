/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:58:56 by minakim           #+#    #+#             */
/*   Updated: 2023/10/24 17:00:06 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_resource	*rsc_instance(void)
{
	static t_resource	this;
	static int			is_init;

	if (is_init)
		return (&this);
	this = (t_resource){
			.n_philos = 0,
			.time_die = 0,
			.time_eat = 0,
			.time_jam = 0,
			.required_eat = -1,
			.time_table = NULL,
			.next = NULL,
			.philos = NULL,
			.philosophers = NULL,
			.forks = NULL,
			.printlock = {},
			.funeral = 0,
	};
	is_init = TRUE;
	return (&this);
}

void	eat(t_philo *philo, t_resource *rsc)
{

}

void	jam(t_philo *philo, t_resource *rsc)
{

}

void	think(t_philo *philo, t_resource *rsc)
{

}

int	rightfork(int target_philo, int total_philos)
{
	int	res;

	res = (target_philo + 1) % total_philos;
	return (res);
}

t_philo	*set_philo(int id, pthread_mutex_t *r_fork, pthread_mutex_t *l_fort)
{
	t_philo	*this;

	this = (t_philo *)malloc(sizeof(t_philo));
	this->id = id;
	this->r_fork = r_fork;
	this->l_fork = l_fort;
	this->s = none;
	this->n_ate = 0;
	this->t_last_meal = 0;
	this->t_launch = 0;
	return (this);
}

void	init_thread_mutex(t_resource *rsc, int n_philo)
{
	int				i;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

	i = -1;
	while (++i < NUM_STATUS_MSGS)
		pthread_mutex_init(rsc->printlock[i], NULL);
	i = -1;
	while (++i < n_philo)
	{
		rsc->philosophers[i] = malloc(sizeof(pthread_t) * 1);
		rsc->forks[i] = malloc(sizeof(pthread_mutex_t) * 1);
	}
	i = -1;
	while (++i < n_philo)
	{
		pthread_mutex_init(rsc->forks[i], NULL);
		pthread_mutex_init(rsc->forks[rightfork(i, n_philo)], NULL);
		left = rsc->forks[i];
		right = rsc->forks[rightfork(i, n_philo)];
		rsc->philos[i] = set_philo(i, left, right);
	}
}

void	init_time_table(t_resource *rsc, int n_philo, int i, int ph_id)
{
	if (i >= n_philo)
		return;
	if (ph_id < n_philo)
	{
		rsc->time_table[i] = ph_id;
		init_time_table(rsc, n_philo, i + 1, ph_id + 2);
	}
	else
		init_time_table(rsc, n_philo, i, ph_id - n_philo + 1);
}

t_resource	*init_rsc(int n_philo, int t_die, int t_eat, int t_jam)
{
	t_resource	*rsc;
	int			i;

	rsc = rsc_instance();
	rsc->n_philos = n_philo;
	rsc->time_die = t_die;
	rsc->time_eat = t_eat;
	rsc->time_jam = t_jam;
	rsc->time_table = (int *)malloc(sizeof(int) * n_philo);
	rsc->philos = (t_philo **)malloc(sizeof(t_philo *) * n_philo);
	rsc->philosophers = (pthread_t **)malloc(sizeof(pthread_t *) * n_philo);
	rsc->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * n_philo);
	init_time_table(rsc, n_philo, 0, 0);
	i = -1;
	while (++i < NUM_STATUS_MSGS)
		rsc->printlock[i] = malloc(sizeof(pthread_mutex_t) * 1);
	init_thread_mutex(rsc, n_philo);
	return (rsc);
}

void	*death_occurrence(t_philo *philo)
{
	// make target philo die.
	// print handler for death.
}

void	*lifecycle(t_philo *philo)
{
	t_resource	*rsc;

	rsc = rsc_instance();
	if (rsc->n_philos == 1)
		return (death_occurrence(philo));
	while (!rsc->funeral)
	{
		eat(philo, rsc);
		jam(philo, rsc);
		think(philo, rsc);
	}
}

int	prepare_dining_table(t_resource *rsc)
{
	int	i;

	i = -1;
	while (++i < rsc->n_philos)
	{
		rsc->philos[i]->t_launch = ft_get_time();
		rsc->philos[i]->t_last_meal = rsc->philos[i]->t_launch;
		if (!pthread_create(rsc->philosophers[i], NULL,
	(void *) lifecycle, rsc->philos[i]))
			return (FALSE);
	}
	return (TRUE);
}

void	status_checker()
{

}

/// [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]
/// && [number_of_times_each_philosophers_must_eat]
int main(int ac, char **av)
{
	t_resource	*rsc;

	if (check_valid_args(ac, av) != 0)
		return (1);
	rsc = init_rsc(ft_atoi(av[1]), ft_atoi(av[2]), \
		ft_atoi(av[3]), ft_atoi(av[4]));
	if (ac == 6)
		rsc->required_eat = ft_atoi(av[5]);
	/// pthread_create (start), return (error)
	if (!prepare_dining_table(rsc))
		return (exit(1), 1);
	/// while loop (philos alive)
	while (!rsc->funeral && rsc->required_eat < 0)
	{
		status_checker();
		usleep(100);
	}
	/// Join threads here

	/// Free resources here
	return (0);
}