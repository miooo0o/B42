/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:17:41 by minakim           #+#    #+#             */
/*   Updated: 2023/12/11 16:03:53 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		philosophers(t_data *data);
void	cleanup(t_data *data);
void	prepare_philo(t_data *data);

int	philosophers(t_data *data)
{
	int	i;

	prepare_philo(data);
	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_create(&data->arr_m_philos[i].pth, NULL, \
		ft_lifecycle, &data->arr_m_philos[i]) != 0)
			return (cleanup(data), ft_perror(ETHREADCREATE), FALSE);
	}
	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_create(&data->arr_m_philos[i].mon_pth, NULL, \
		ft_monitor, &data->arr_m_philos[i]) != 0)
			return (cleanup(data), ft_perror(ETHREADCREATE), FALSE);
	}
	i = -1;
	while (++i < data->n_philos)
		pthread_join(data->arr_m_philos[i].pth, NULL);
	i = -1;
	while (++i < data->n_philos)
		pthread_join(data->arr_m_philos[i].mon_pth, NULL);
	return (cleanup(data), TRUE);
}

void	prepare_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		data->arr_m_philos[i].creation_us = ft_gettime_us();
		data->arr_m_philos[i].last_meal_us = ft_gettime_us();
		data->arr_m_philos[i].is_fulled = FALSE;
		data->arr_m_philos[i].death_occurs = FALSE;
		data->arr_m_philos[i].urgent_us = round_ms(data->die_us / DIVIDE_BY);
	}
}

void	cleanup(t_data *data)
{
	int	n_philo;
	int	i;

	n_philo = data->n_philos;
	i = -1;
	while (++i < n_philo)
	{
		pthread_mutex_destroy(&data->arr_m_philos[i].mx_meal);
		pthread_mutex_destroy(&data->arr_m_philos[i].mx_state);
	}
	i = -1;
	while (++i < n_philo)
		pthread_mutex_destroy(&data->arr_m_forks[i]);
	pthread_mutex_destroy(&data->mx_log);
	pthread_mutex_destroy(&data->mx_death);
	free(data->arr_m_philos);
	free(data->arr_m_forks);
}

