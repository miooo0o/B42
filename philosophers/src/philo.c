/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:58:56 by minakim           #+#    #+#             */
/*   Updated: 2023/10/23 18:09:33 by minakim          ###   ########.fr       */
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

void	*philosopher(t_philo *philo)
{
	t_resource	*rsc;

	rsc = rsc_instance();

	/// philo dead
	if (rsc->n_philos == 1)
		return (0);
	while (!rsc->funeral)
	{
		eat(philo, rsc);
		jam(philo, rsc);
		think(philo, rsc);
	}

}

int	rightfork(int target_philo, int total_philos)
{
	int	res;

	res = (target_philo + 1) % total_philos;
	return (res);
}

void	init_thread_mutex(t_resource *rsc, int n_philo)
{
	int				i;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

	i = -1;
	while (++i < 5)
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
		rsc->philos[i] = new_philo(i, left, right);
	}
	return ;
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
	rsc->time_table = malloc(sizeof(int) * n_philo);
	rsc->philos = malloc(sizeof(t_philo *) * n_philo);
	rsc->philosophers = malloc(sizeof(pthread_t *) * n_philo);
	rsc->forks = malloc(sizeof(pthread_mutex_t *) * n_philo);
	init_time_table(rsc, n_philo, 0, 0);
	i = -1;
	while (++i < NUM_STATUS_MSGS)
		rsc->printlock[i] = malloc(sizeof(pthread_mutex_t) * 1);
	init_thread_mutex(rsc, n_philo);
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

	return (0);
}