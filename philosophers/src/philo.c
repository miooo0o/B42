/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:58:56 by minakim           #+#    #+#             */
/*   Updated: 2023/10/10 21:26:32 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_resource	*resource_instance(void)
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
			.n_eat_opt = 0,
	};
	is_init = 1;
	return (&this);
}

int	eat(t_philo *philo, t_resource *rsc)
{

	return (1);
}

int jam(t_philo *philo, t_resource *rsc)
{

	return (1);
}

int	think(t_philo *philo, t_resource *rsc)
{

	return (1);
}

void	*philosopher(t_philo *philo)
{
	t_resource	*rsc;

	rsc = resource_instance();

	/// philo dead
	if (rsc->n_philos == 1)
		return (0);
	while (rsc->no_deaths)
	{
		eat(philo, rsc);
		jam(philo, rsc);
		think(philo, rsc);
	}

}

int main(int ac, char **av)
{
	if (check_args(ac, av) != 0)
		return (1);

	return (0);
}