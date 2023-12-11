/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:06:16 by minakim           #+#    #+#             */
/*   Updated: 2023/12/11 16:27:00 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lonely_philo(t_philo *philo)
{
	print_log(philo, THINK);
	print_log(philo, FORK);
	usleep(philo->die_us);
	print_log(philo, DIE);
}

int	should_terminate_cycle(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mx_death);
	if (philo->death_occurs || philo->is_fulled)
	{
		pthread_mutex_unlock(&philo->data->mx_death);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->data->mx_death);
	return (FALSE);
}

void	*ft_lifecycle(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->n_philos == 1)
		return (lonely_philo(philo), NULL);
	while (!should_terminate_cycle(philo))
	{
		print_log(philo, THINK);
		eat(philo);
		print_log(philo, SLEEP);
		usleep(philo->jam_us);
	}
	return (NULL);
}

