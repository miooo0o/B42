/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:51:37 by minakim           #+#    #+#             */
/*   Updated: 2023/12/05 15:24:30 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	t_bool	res;

	res = FALSE;
	pthread_mutex_lock(&philo->mx_meal);
	if (philo->left_meal &&
		(ft_gettime_us() - philo->last_meal_us > philo->die_us))
		res = TRUE;
	pthread_mutex_unlock(&philo->mx_meal);
	return (res);
}

void	a_sudden_death_is_the_best(t_philo *philo)
{
	int i;

	i = -1;
	pthread_mutex_lock(&philo->mx_meal);
	print_log(philo, DIE);
	pthread_mutex_lock(&philo->data->mx_death);
	while (++i < philo->n_philos)
		philo->data->arr_m_philos[i].death_occurs = TRUE;
	pthread_mutex_unlock(&philo->data->mx_death);
	pthread_mutex_unlock(&philo->mx_meal);
}

int	check_fullness(t_philo *philo)
{
	t_bool	res;

	res = FALSE;
	pthread_mutex_lock(&philo->mx_meal);
	if (philo->is_fulled)
		res = TRUE;
	pthread_mutex_unlock(&philo->mx_meal);
	return (res);
}

void	*ft_monitor(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (check_death(philo))
			return (a_sudden_death_is_the_best(philo), NULL);
		else if (check_fullness(philo))
			return (NULL);
	}
}
