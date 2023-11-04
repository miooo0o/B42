/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:02:35 by minakim           #+#    #+#             */
/*   Updated: 2023/11/03 18:20:07 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

#define RESET_INDEX -1

void	*death_occurrence(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_status(philo, rsc_instance(), "has taken a fork", LOG_STATUS);

	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}

void	update_next_entry(t_resource *rsc)
{
	static int	i;
	int			last_index;

	last_index = rsc->n_philos - 1;
	pthread_mutex_lock(rsc->m_lock[LOG_NEXT_UPDATE]);
	rsc->next = &(rsc->time_table[++i]);
	if (i >= last_index)
		i = RESET_INDEX;
	pthread_mutex_unlock(rsc->m_lock[LOG_NEXT_UPDATE]);
}

void	eat(t_philo *philo, t_resource *rsc)
{
	long long	time_to_eat;

	time_to_eat = 0;

	pthread_mutex_lock(philo->l_fork);
	print_status(philo, rsc, "has taken a fork", LOG_STATUS);
	pthread_mutex_lock(philo->r_fork);
	print_status(philo, rsc, "has taken a fork", LOG_STATUS);
	update_next_entry(rsc);
	print_status(philo, rsc, "is eating", LOG_STATUS);
	time_to_eat = rsc->time_eat + philo->t_last_meal;
//	printf("update time to me as %lld\n", time_to_eat);
	while (time_to_eat > ft_get_time())
		usleep(100);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->t_last_meal = time_to_eat;
	philo->n_ate++;
}

void	jam(t_philo *philo, t_resource *rsc)
{
	long long	target_time;

	target_time = rsc->time_jam + ft_get_time();
	print_status(philo, rsc, "is sleeping", LOG_STATUS);
	while (target_time > ft_get_time())
		usleep(100);
	return ;
}

void	think(t_philo *philo, t_resource *rsc)
{
	print_status(philo, rsc, "is thinking", LOG_STATUS);
	return ;
}
