/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:41:38 by minakim           #+#    #+#             */
/*   Updated: 2023/11/14 16:50:27 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_rsc	*rsc_instance(void)
{
	static t_rsc	this;
	static int	is_init = FALSE;

	if (is_init)
		return (&this);
	this = (t_rsc){
		.arr_m_forks = NULL,
		.arr_m_n_eaten = NULL,
		.arr_m_status = NULL,
		.arr_m_last_meal = NULL,
		.print = 0,
		.arr_m_philos = NULL
	};
	is_init = TRUE;
	return (&this);
}

t_data	*data_instance(void)
{
	static t_data	this;
	static int	is_init = FALSE;

	if (is_init)
		return (&this);
	this = (t_data){
		.n_philos = -1,
		.time_die = -1,
		.time_eat = -1,
		.time_jam = -1,
		.required_n_meals = -1
	};
	is_init = TRUE;
	return (&this);
}

t_exit	init_rsc(int n_philos)
{
	t_rsc	*rsc;
	t_exit	exit;

	rsc = rsc_instance();
	/// FIXME: free rsc
	/// @note 여기 뮤텍스 != SUCCESS 일때 재대로 보호하기!

	exit = init_arr_m_mutex(n_philos, &(rsc->arr_m_n_eaten));
	if (exit != SUCCESS)
		return (exit);
	exit = init_arr_m_mutex(n_philos, &(rsc->arr_m_forks));
	if (exit != SUCCESS)
		return (free(rsc->arr_m_n_eaten), exit);

	exit = init_arr_m_mutex(n_philos, &(rsc->arr_m_status));
	if (exit == SUCCESS)
		exit = init_arr_m_mutex(n_philos, &(rsc->arr_m_last_meal));
	if (exit == SUCCESS)
		rsc->arr_m_philos = ft_memalloc(sizeof (t_philo) * n_philos);
	if (!rsc->arr_m_philos)
		return (free(rsc->arr_m_n_eaten), free(rsc->arr_m_forks),
				MEM_ERROR);
	if (pthread_mutex_init(&rsc->print, NULL) != 0)
		return (INIT_ERROR);
	rsc->data = data_instance();
	return (exit);
}

t_philo	init_one_philo(t_rsc *rsc, int i)
{
	t_philo	one;

	one = (t_philo) {
		.id = i,
		.l_fork = &(rsc->arr_m_forks[i]),
		.r_fork = &(rsc->arr_m_forks[i + 1]),
		.meal = &(rsc->arr_m_n_eaten[i]),
		.n_eaten = 0,
		.step = NONE_SET,
		.is_alive = TRUE,
		.last_meal = 0,
		.creation_time = 0,
	};
	return (one);
}

t_exit	init_philos(int n_philos)
{
	t_rsc	*rsc;
	int 	i;

	rsc = rsc_instance();
	i = -1;

	while (++i < n_philos)
		rsc->arr_m_philos[i] = init_one_philo(rsc, i);
	if (i > 0 && i == n_philos)
		rsc->arr_m_philos[i].r_fork = &rsc->arr_m_forks[0];
	return (SUCCESS);
}

t_exit	init(int argc, char **argv)
{
	t_exit	exit;
	t_data	*data;

	data = data_instance();
	exit = init_rsc(data->n_philos);
	if (exit == SUCCESS)
		exit = init_philos(data->n_philos);
	return (exit);
}