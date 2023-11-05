/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:08:31 by minakim           #+#    #+#             */
/*   Updated: 2023/11/05 23:01:29 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	manage_dining(t_config *handler)
{

}

int	main(int ac, char **av)
{
	t_config	*conf;
	t_philo		**philos;

	conf = config_from_args(ac, av);
	if (!conf)
		return (printf("something happen...\n"), 1);
	philos = init_philos(conf);
	if (!philos)
	{
		ft_free_2d((void *)conf->forks);
		return (ft_error_type(PHILO_INIT), 1);
	}
	if (philosophers(conf, philos) == 0)
		printf("SUCCESS\n");
	return (0);
}
