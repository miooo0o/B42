/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:29:18 by minakim           #+#    #+#             */
/*   Updated: 2023/12/05 16:54:58 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	int	i;
	int	exit;

	i = 0;
	while (++i < ac)
	{
		if (!ft_all_satisfy(ft_isdigit, av[i]))
			return (FALSE);
		exit = ft_atoi(av[i]);
		if (exit == -1)
			return (FALSE);
	}
	if (ft_atoi(av[1]) >= MAX_PHILOS)
		return (FALSE);
	return (TRUE);
}

static void	init_forks(t_data *data, int i)
{
	data->arr_m_philos[i].r_fork.mx = &data->arr_m_forks[i];
	data->arr_m_philos[i].r_fork.is_taken = FALSE;
	if (i != 0)
	{
		data->arr_m_philos[i].l_fork.mx = &data->arr_m_forks[i - 1];
		data->arr_m_philos[i].l_fork.is_taken = FALSE;
	}
}

/// Hold the fork corresponding to target's index on the right,
/// and the fork of the other philosopher on the left.
static void	init_each_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
		pthread_mutex_init(&data->arr_m_forks[i], NULL);
	i = -1;
	while (++i < data->n_philos)
	{
		pthread_mutex_init(&data->arr_m_philos[i].mx_meal, NULL);
		data->arr_m_philos[i].id = i + 1;
		data->arr_m_philos[i].n_philos = data->n_philos;
		data->arr_m_philos[i].die_us = data->die_us;
		data->arr_m_philos[i].eat_us = data->eat_us;
		data->arr_m_philos[i].jam_us = data->jam_us;
		data->arr_m_philos[i].left_meal = data->required_meals;
		data->arr_m_philos[i].data = data;
		init_forks(data, i);
	}
	if (data->n_philos > 1)
	{
		data->arr_m_philos[0].l_fork.mx = \
			&data->arr_m_forks[data->n_philos - 1];
		data->arr_m_philos[0].l_fork.is_taken = FALSE;
	}
}

t_bool	init_data(int ac, char **av, t_data *data)
{
	data->n_philos = ft_atoi(av[1]);
	data->die_us = ft_atoi(av[2]) * 1000;
	data->eat_us = ft_atoi(av[3]) * 1000;
	data->jam_us = ft_atoi(av[4]) * 1000;
	if (ac == 6)
		data->required_meals = ft_atoi(av[5]);
	else
		data->required_meals = NONE;
	data->arr_m_philos = ft_memalloc(sizeof(t_philo) * data->n_philos);
	if (!data->arr_m_philos)
		return (FALSE);
	data->arr_m_forks = ft_memalloc(sizeof(t_mutex) * data->n_philos);
	if (!data->arr_m_forks)
		return (free(data->arr_m_philos), FALSE);
	pthread_mutex_init(&data->mx_log, NULL);
	pthread_mutex_init(&data->mx_death, NULL);
	init_each_philo(data);
	if (data->n_philos == 1)
		data->arr_m_philos[0].l_fork.mx = NULL;
	return (TRUE);
}
