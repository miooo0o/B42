/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:46:15 by minakim           #+#    #+#             */
/*   Updated: 2023/11/28 16:24:35 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_exit	check_args(int argc, char **argv)
{
	int i;
	int exit;

	i = 0;
	if (!(argc == 5 || argc == 6))
		return (INPUT_VALID_ERR);
	while (++i < argc)
	{
		exit = 0;
		if (!ft_all_satisfy(ft_isdigit, argv[i]))
			return (INPUT_VALID_ERR);
		exit = ft_atoi(argv[i]);
		if (exit == -1)
			return (INPUT_VALID_ERR);
	}
	return (SUCCESS);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)ft_memalloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->n_philos = ft_atoi(argv[1]);
	data->last_philo_id = data->n_philos - 1;
	data->time_die_usec = ft_atoi(argv[2]) * 1000;
	data->time_eat_usec = ft_atoi(argv[3]) * 1000;
	data->time_jam_usec = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
	{
		data->required_n_meals = ft_atoi(argv[5]);
		data->is_n_meals_finished = FALSE;
	}
	else
		data->is_n_meals_finished = NONE;
	data->all_alive = NONE;
	data->arr_m_philos = NULL;
	data->arr_m_forks = NULL;
	return (data);
}