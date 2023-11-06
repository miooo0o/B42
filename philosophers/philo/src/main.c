/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:58:56 by minakim           #+#    #+#             */
/*   Updated: 2023/11/06 19:34:56 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
# define TRUE 1

/// [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]
/// && [number_of_times_each_philosophers_must_eat]
int main(int ac, char **av)
{
	t_resource	*rsc;

	if (!valid_args(ac, av))
		return (0);
	manage_dining();
	return (0);
}

///
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
			.p_threads = NULL,
			.forks = NULL,
			.m_lock = NULL,
			.funeral = 0,
	};
	is_init = TRUE;
	return (&this);
}
