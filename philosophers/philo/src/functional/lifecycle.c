/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:01:48 by minakim           #+#    #+#             */
/*   Updated: 2023/11/21 18:46:49 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eat(t_philo *philo, t_rsc *rsc);
void	*jam(t_philo *philo, t_rsc *rsc);
void	*think(t_philo *philo, t_rsc *rsc);

void	*jam(t_philo *philo, t_rsc *rsc)
{
	if (all_alive(philo))
	{
		ft_print(philo, SLEEP);
		ft_usleep(rsc->data->time_jam);
		think(philo, rsc);
	}
	usleep(3);
	return (NULL);
}

void	*think(t_philo *philo, t_rsc *rsc)
{
	if (all_alive(philo))
	{
		ft_print(philo, THINK);
		eat(philo, rsc);
	}
	usleep(3);
	return (NULL);
}

void	lonely_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	ft_print(philo, FORK);
	pthread_mutex_unlock(philo->l_fork);
	ft_usleep(data_instance()->time_eat);
	return ;
}

void	update_eating_philo_id(void)
{
	t_mutex	*mutex_timetable;
	t_rsc	*rsc;
	static int i = 0;

	rsc = rsc_instance();
	mutex_timetable = &(rsc_instance()->timetable);
	pthread_mutex_lock(mutex_timetable);
	if (i >= rsc->data->n_philos - 1)
		i = -1;
	rsc->who_next = &(rsc->arr_m_timetable[++i]);
	pthread_mutex_unlock(mutex_timetable);
}



void 	grab_forks(t_philo *philo)
{
	t_rsc *rsc;

	rsc = rsc_instance();
	pthread_mutex_lock(&(rsc->timetable));
	while (*(rsc->who_next) != philo->id)
	{
		pthread_mutex_unlock(&(rsc->timetable));
		if (!all_alive(philo))
			return ;
//		ft_usleep(CHECK_INTERVAL);
		pthread_mutex_lock(&(rsc->timetable));
	}
	usleep(CHECK_INTERVAL);
	pthread_mutex_unlock(&(rsc->timetable));
	if (!all_alive(philo))
		return ;
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	ft_print(philo, FORK);
	ft_print(philo, FORK);
	if (!all_alive(philo))
		return ;
}

void 	drop_forks(t_philo *philo)
{
	if (!all_alive(philo))
		return ;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	ft_usleep(CHECK_INTERVAL);
}

void	update_last_meal(t_philo *philo, t_rsc *rsc)
{
	pthread_mutex_lock(&(rsc->arr_m_last_meal[philo->id]));
	philo->last_meal = ft_gettime();
	pthread_mutex_unlock(&(rsc->arr_m_last_meal[philo->id]));
}

void	update_n_eaten(t_philo *philo, t_rsc *rsc)
{
	pthread_mutex_lock(&(rsc->arr_m_n_eaten[philo->id]));
	philo->n_eaten += 1;
	pthread_mutex_unlock(&(rsc->arr_m_n_eaten[philo->id]));
}
/// 홀수 번째 철학자는 왼오, 짝수번째 철학자는 오왼 순서
void	*eat(t_philo *philo, t_rsc *rsc)
{
	if (!all_alive(philo))
		return (NULL);
	grab_forks(philo);
	if (!all_alive(philo))
		return (drop_forks(philo), NULL);
	ft_print(philo, EAT);
	if (!all_alive(philo))
		return (drop_forks(philo), NULL);
	update_last_meal(philo, rsc);
	update_eating_philo_id();
	ft_usleep(data_instance()->time_eat);
	update_n_eaten(philo, rsc);
	drop_forks(philo);
	jam(philo, rsc);
	return (NULL);
}

void	*lifecycle(void *p)
{
	t_philo	*philo;
	t_rsc	*rsc;

	philo = (t_philo *)p;
	rsc = rsc_instance();
	if (rsc->data->n_philos == 1)
	{
		lonely_philo(philo);
		return (NULL);
	}
	eat(philo, rsc);
	return (NULL);
}