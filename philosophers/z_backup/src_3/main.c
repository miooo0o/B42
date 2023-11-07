/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:20:19 by minakim           #+#    #+#             */
/*   Updated: 2023/11/07 17:09:38 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_3.h"

t_rsc	*rsc_instance(void)
{
	static t_rsc		this;
	static int			is_init;

	if (is_init)
		return (&this);
	this = (t_rsc){
		.n_philos = 0,
		.time_die = 0,
		.time_eat = 0,
		.time_jam = 0,
		.required_meal = 0,
		.status = STATUS_RUNNING,
		.locks = NULL,
		.forks = NULL
	};
	is_init = TRUE;
	return (&this);
}

int	main(int argc, char **argv)
{
	t_philo **philos;
	t_rsc	*rsc;

	if (!valid_args(argc, argv) || !init_rsc())
		return (1);
	rsc = rsc_instance();
	philos = init_philos(rsc);

	/// <<< start threads here
	philosopers(philos);
	return (0);

}