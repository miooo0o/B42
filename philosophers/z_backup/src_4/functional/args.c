/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:42:36 by minakim           #+#    #+#             */
/*   Updated: 2023/11/19 20:35:17 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo_4.h"

void	init_data(int argc, char **argv)
{
	t_data	*data;

	data = data_instance();
	data->n_philos = ft_atoi(argv[1]);
	data->last_philo_id = data->n_philos - 1;
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_jam = ft_atoi(argv[4]);
	if (argc == 6)
		data->required_n_meals = ft_atoi(argv[5]);
}

t_exit	check_args(int argc, char **argv)
{
	int i;
	int exit;

	i = 0;
	if (!(argc == 5 || argc == 6))
		return (INPUT_VALID_ERROR);
	while (++i < argc)
	{
		exit = 0;
		if (!ft_all_satisfy(ft_isdigit, argv[i]))
			return (ft_error_msg("input should be digit only"), INPUT_VALID_ERROR);
		exit = ft_atoi(argv[i]);
		if (exit == -1)
			return (ft_error_msg("too large value"), INPUT_VALID_ERROR);
	}
	init_data(argc, argv);
	return (SUCCESS);
}
