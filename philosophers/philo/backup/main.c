/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:08:58 by minakim           #+#    #+#             */
/*   Updated: 2023/11/30 16:26:52 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <assert.h> /// @note delete later

void	prepare_philo(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->n_philos)
	{
		data->arr_m_philos[i].creation_us = ft_gettime_us();
		data->arr_m_philos[i].last_meal_us = ft_gettime_us();
		data->arr_m_philos[i].is_fulled = FALSE;
		data->arr_m_philos[i].death_occurs = FALSE;
		if (data->required_meals > 0)
			data->arr_m_philos[i].left_meal = data->required_meals;
	}
}

int	philosophers(t_data *data)
{
	int i;


	prepare_philo(data);
	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_create(&data->arr_m_philos[i].pth, NULL,
						   ft_lifecycle, &data->arr_m_philos[i]) != 0)
			return (ft_perror(ETHREADCREATE), FALSE);
	}
	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_create(&data->arr_m_philos[i].mon_pth, NULL,
						   ft_monitor, &data->arr_m_philos[i]) != 0)
			return (ft_perror(ETHREADCREATE), FALSE);
	}
	i = -1;
	while (++i < data->n_philos)
		pthread_join(data->arr_m_philos[i].pth, NULL);
	i = -1;
	while (++i < data->n_philos)
		pthread_join(data->arr_m_philos[i].mon_pth, NULL);
	return (/* clean && free */ EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (ft_perror(EINARGNUM), EXIT_FAILURE);
	if (!check_args(ac, av))
		return (ft_perror(EINVAL), EXIT_FAILURE);
	if (!init_data(ac, av, &data))
		return (ft_perror(ENOMEM), EXIT_FAILURE);
	if (!philosophers(&data))
		return (EXIT_FAILURE);
	write(STDOUT_FILENO, "philosophers\n", 14);
	return (EXIT_SUCCESS);
}