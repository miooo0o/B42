/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:20:57 by minakim           #+#    #+#             */
/*   Updated: 2023/11/21 00:12:23 by minakim          ###   ########.fr       */
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