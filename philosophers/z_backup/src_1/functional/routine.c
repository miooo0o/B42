/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:02:35 by minakim           #+#    #+#             */
/*   Updated: 2023/11/06 20:07:48 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define RESET_INDEX -1

void	*death_occurrence(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_status(philo, rsc_instance(), "has taken a fork", L_PRINT);

	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}

void	update_next_entry(t_resource *rsc)
{
	static int	i;
	int			last_index;

	last_index = rsc->n_philos - 1;
	pthread_mutex_lock(rsc->m_lock[L_NEXT_UPDATE]);
	rsc->next = &(rsc->time_table[++i]);
	if (i >= last_index)
		i = RESET_INDEX;
	pthread_mutex_unlock(rsc->m_lock[L_NEXT_UPDATE]);
}

void	eat(t_philo *philo, t_resource *rsc)
{
	long long	time_to_eat;

	time_to_eat = 0;

	pthread_mutex_lock(philo->l_fork);
	print_status(philo, rsc, "has taken a fork", L_PRINT);
	pthread_mutex_lock(philo->r_fork);
	print_status(philo, rsc, "has taken a fork", L_PRINT);
	update_next_entry(rsc);
	print_status(philo, rsc, "is eating", L_PRINT);
//	printf("update time to %lld\n", time_to_eat - ft_get_time());

	pthread_mutex_lock(rsc->m_lock[L_TIME]);
	time_to_eat = rsc->time_eat + philo->t_last_meal;
	while (time_to_eat > ft_get_time())
		usleep(100);
	pthread_mutex_unlock(rsc->m_lock[L_TIME]);

	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);

	pthread_mutex_lock(rsc->m_lock[L_MEAL]);
	philo->t_last_meal = time_to_eat;
	philo->n_ate++;
	pthread_mutex_unlock(rsc->m_lock[L_MEAL]);


}

void	jam(t_philo *philo, t_resource *rsc)
{
	long long	target_time;

	pthread_mutex_lock(rsc->m_lock[L_TIME]);
	target_time = rsc->time_jam + ft_get_time();
	print_status(philo, rsc, "is sleeping", L_PRINT);
	while (target_time > ft_get_time())
		usleep(100);
	pthread_mutex_unlock(rsc->m_lock[L_TIME]);
	return ;
}

void	think(t_philo *philo, t_resource *rsc)
{
	print_status(philo, rsc, "is thinking", L_PRINT);
	return ;
}
