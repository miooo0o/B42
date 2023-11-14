/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:41:38 by minakim           #+#    #+#             */
/*   Updated: 2023/11/14 10:52:30 by minakim          ###   ########.fr       */
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
		.arr_m_fork = NULL,
		.arr_m_lock = NULL,
		.print = 0,
		.death = 0,
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
	exit = SUCCESS;
	exit = init_arr_m_mutex(n_philos, &(rsc->arr_m_lock));
	if (exit != SUCCESS)
		return (exit);
	exit = init_arr_m_mutex(n_philos, &(rsc->arr_m_fork));
	if (exit != SUCCESS)
		return (free(rsc->arr_m_lock), exit);
	rsc->arr_m_philos = ft_memalloc(sizeof (t_philo) * n_philos);
	if (!rsc->arr_m_philos)
		return (free(rsc->arr_m_lock), free(rsc->arr_m_fork),
				MEM_ERROR);
	if (pthread_mutex_init(&rsc->print, NULL) != 0)
		return (INIT_ERROR); /* FIXME: free rsc*/
	if (pthread_mutex_init(&rsc->death, NULL) != 0)
		return (pthread_mutex_destroy(&rsc->print), INIT_ERROR); /* FIXME: free rsc*/
	return (exit);
}

t_philo	init_one_philo(t_rsc *rsc, int i)
{
	t_philo	one;

	one = (t_philo) {
		.id = i,
		.l_fork = &(rsc->arr_m_fork[i]),
		.r_fork = &(rsc->arr_m_fork[i]),
		.lock = &(rsc->arr_m_lock[i]),
		.n_eaten = 0,
		.step = NONE_SET,
		.is_alive = TRUE,
		.last_meal = 0,
		.creation_time = 0
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