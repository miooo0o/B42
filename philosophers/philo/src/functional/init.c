/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:41:38 by minakim           #+#    #+#             */
/*   Updated: 2023/11/13 15:46:41 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_rsc	*rsc_instance(void)
{
	static t_rsc	this;
	static int	is_init;
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
}

t_data	*data_instance(void)
{
	static t_data	this;
	static int	is_init;
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
}

void	init_data(int argc, char **argv)
{
	t_data	*data;

	data = data_instance();
	data->n_philos = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_jam = ft_atoi(argv[4]);
	if (argc == 6)
		data->required_n_meals = ft_atoi(argv[5]);
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

t_exit	init(int argc, char **argv)
{
	t_exit	exit;
	t_rsc	*rsc;
	t_data	*data;
	t_philo	*philos;

	data = data_instance();
	exit = init_rsc(data->n_philos);
	if (exit == SUCCESS)
		exit = init_philos();
}