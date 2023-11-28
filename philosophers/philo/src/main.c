/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:15:10 by minakim           #+#    #+#             */
/*   Updated: 2023/11/28 16:51:11 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_exit	init_arr_m_forks(t_data *data)
{
	int		i;
	t_fork	*forks;

	forks = NULL;
	forks = ft_memalloc(sizeof(t_fork) * data->n_philos);
	if (forks == NULL)
		return (MEM_ERR);
	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_mutex_init(&(forks[i].m), NULL) != 0)
			return (free(forks), INIT_M_ERR);
	}
	data->arr_m_forks = &forks;
	return (SUCCESS);
}

t_exit	init_single_mutexs(t_data *data)
{
	t_exit	exit;

	exit = NONE;
	exit = pthread_mutex_init(&(data->m_time), NULL);
	if (exit == SUCCESS)
		exit = pthread_mutex_init(&(data->m_dead), NULL);
	if (exit == SUCCESS)
		exit = pthread_mutex_init(&(data->m_death_time), NULL);
	if (exit == SUCCESS)
		exit = pthread_mutex_init(&(data->m_meal), NULL);
	if (exit == SUCCESS)
		exit = pthread_mutex_init(&(data->m_print), NULL);
	return (exit);
}


t_exit	init_arr_m_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = ft_memalloc(sizeof(t_philo) * data->n_philos);
	if (!philos)
		return (MEM_ERR);
	i = -1;
	while (++i < data->n_philos)
	{
		philos[i] = (t_philo){
			.id = i + 1,
			.data = data,
			.last_meal = 0,
			.n_eaten = 0,
			.l_fork = data->arr_m_forks[i],
		};
		if (i == data->n_philos - 1)
			philos->r_fork = data->arr_m_forks[0];
		else
			philos->r_fork = data->arr_m_forks[i + 1];
	}
	data->arr_m_philos = &philos;
	return (SUCCESS);
}

t_exit	init_detail(t_data *data)
{
	t_exit	exit;

	exit = init_single_mutexs(data);
	if (exit != SUCCESS)
		return (exit);
	exit = init_arr_m_forks(data);
	if (exit != SUCCESS)
	{
		/// destroy: init_single_mutexs
		return (exit);
	}
	exit = init_arr_m_philos(data);
	if (exit != SUCCESS)
	{
		/// destroy: init_single_mutexs, init_arr_m_forks, free:  init_arr_m_forks
		return (exit);
	}
	return (exit);
}

t_exit	philosophers(t_data *data)
{

	return (SUCCESS);
}

void	cleanup(t_data *data)
{
	/// destroy init_single_mutexs, mutexs
	/// free philo
	/// free data
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_exit	exit;

	exit = check_args(argc, argv);
	if (exit != INPUT_VALID_ERR)
		ft_err("check_args", exit);

	data = init_data(argc, argv);
	if (data == NULL)
		return (ft_err("init_data", MEM_ERR));

	exit = init_detail(data);
	if (exit != SUCCESS)
		return (ft_err("init_detail", exit));

	exit = philosophers(data);
	if (exit != SUCCESS)
		return (cleanup(data), ft_err("philosophers", exit));

	cleanup(data);
	return (exit);
}
