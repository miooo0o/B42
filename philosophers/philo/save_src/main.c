/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:08:31 by minakim           #+#    #+#             */
/*   Updated: 2023/11/06 18:19:06 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

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
		return (ft_error_type(ERROR_PHILO_INIT), 1);
	}


	/// @test
	printf("time table : ");
	for (int i = -1; ++i < ft_atoi(av[1]);)
		printf("[%d]", conf->time_table[i]);
	printf("\n");


	if (philosophers(conf, philos) == 0)
		printf("SUCCESS\n");
	return (0);
}
