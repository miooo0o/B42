/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_resource.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:28:27 by minakim           #+#    #+#             */
/*   Updated: 2023/11/03 18:10:04 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	this->n_ate = 0;
	this->t_last_meal = 0;
	this->t_creation = 0;
	return (this);
}

void	setup_mutexes(t_resource *rsc, int n_philo)
{
	int				i;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

	i = -1;
	while (++i < NUM_MUTEX_LOGS)
		pthread_mutex_init(rsc->printlock[i], NULL);
	i = -1;
	while (++i < n_philo)
	{
		rsc->p_threads[i] = malloc(sizeof(pthread_t) * 1);
		rsc->forks[i] = malloc(sizeof(pthread_mutex_t) * 1);
		pthread_mutex_init(rsc->forks[i], NULL);
	}
	i = -1;
	while (++i < n_philo)
	{
		l_fork = NULL;
		r_fork = NULL;
//		pthread_mutex_init(rsc->forks[rightfork(i, n_philo)], NULL);
		l_fork = rsc->forks[i];
		r_fork = rsc->forks[rightfork(i, n_philo)];
		rsc->philos[i] = set_philo(i, l_fork, r_fork);
	}
}

void	init_time_table(t_resource *rsc, int n_philo)
{
	int	i;
	int	ph_id;

	i = -1;
	ph_id = 0;
	while (ph_id < n_philo)
	{
		rsc->time_table[++i] = ph_id;
		ph_id += 2;
	}
	ph_id = 1;
	while (ph_id < n_philo)
	{
		rsc->time_table[++i] = ph_id;
		ph_id += 2;
	}
	return ;
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
	rsc->p_threads = (pthread_t **)malloc(sizeof(pthread_t *) * n_philo);
	rsc->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * n_philo);
	init_time_table(rsc, n_philo);
	i = -1;
	while (++i < NUM_MUTEX_LOGS)
		rsc->printlock[i] = malloc(sizeof(pthread_mutex_t) * 1);
	setup_mutexes(rsc, n_philo);

	/// TODO: it is test function, del later
	i = -1;
	printf("time table :");
	while (++i < rsc->n_philos)
		printf("[%d] ", rsc->time_table[i]);
	printf("\n");

	rsc->next = &(rsc->time_table[0]);
	return (rsc);
}