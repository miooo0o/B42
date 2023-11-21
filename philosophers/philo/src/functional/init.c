/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:41:38 by minakim           #+#    #+#             */
/*   Updated: 2023/11/21 01:20:45 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_exit	init_arr_m_mutex(int count, t_mutex **target)
{
	int		i;
	t_mutex	*this;

	this = NULL;
	this = ft_memalloc(sizeof(t_mutex) * count);
	if (this == NULL)
		return (MEM_ERROR);
	i = -1;
	while (++i < count)
	{
		if (pthread_mutex_init(&this[i], NULL) != 0)
			return (free(this), INIT_ERROR);
	}
	*target = this;
	return (SUCCESS);
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
	if (pthread_mutex_init(&rsc->timetable, NULL) != 0)
		return (INIT_ERROR);
	rsc->data = data_instance();
	return (exit);
}

t_philo	init_one_philo(t_rsc *rsc, int i)
{
	t_philo	one;

	one = (t_philo) {
		.id = i,
		.l_fork = &(rsc->arr_m_forks)[i],
		.n_eaten = 0,
		.is_alive = TRUE,
		.last_meal = ft_gettime(),
		.creation_time = 0,
	};
	return (one);
}

int	rightfork(int target_philo, int total_philos)
{
	return ((target_philo + 1) % total_philos);
}

t_exit	init_philos(int n_philos)
{
	t_rsc	*rsc;
	int 	i;

	rsc = rsc_instance();
//	last_philo_id = rsc->data->last_philo_id;
	if (n_philos == 1)
	{
		rsc->arr_m_philos[0] = init_one_philo(rsc, 0);
		rsc->arr_m_philos[0].r_fork = NULL;
		return (SUCCESS);
	}
	i = -1;
	while (++i < n_philos)
	{
		rsc->arr_m_philos[i] = init_one_philo(rsc, i);
		rsc->arr_m_philos[i].r_fork = &rsc->arr_m_forks[rightfork(i, n_philos)];
		printf("philo [%d] has %d l_fork, %d r_fork\n", i , i, rightfork(i, n_philos) );
		//		if (i == last_philo_id && i > 0)
//			rsc->arr_m_philos[i].r_fork = &rsc->arr_m_forks[0];
//		else
//			rsc->arr_m_philos[i].r_fork = &rsc->arr_m_forks[i + i];
	}
	return (SUCCESS);
}

t_exit	init_timetable(int n_philos)
{
	int	i;
	int	id;
	int *target;
	t_rsc	*rsc;

	rsc = rsc_instance();
	target = ft_memalloc(sizeof(int) * n_philos);
	if (!target)
		return (MEM_ERROR);
	i = -1;
	id = 0;
	while (id < n_philos)
	{
		target[++i] = id;
		id += 2;
	}
	id = 1;
	while (id < n_philos)
	{
		target[++i] = id;
		id += 2;
	}
	rsc->who_next = &(target[0]);
	rsc->arr_m_timetable = target;
	return (SUCCESS);
}

t_exit	init(void)
{
	t_exit	exit;
	t_data	*data;

	data = data_instance();
	exit = init_rsc(data->n_philos);
	if (exit == SUCCESS)
		exit = init_philos(data->n_philos);
	if (exit == SUCCESS)
		exit = init_timetable(data->n_philos);
	return (exit);
}