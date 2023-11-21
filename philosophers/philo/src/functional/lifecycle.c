/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:01:48 by minakim           #+#    #+#             */
/*   Updated: 2023/11/21 01:19:52 by minakim          ###   ########.fr       */
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
	return (NULL);
}

void	*think(t_philo *philo, t_rsc *rsc)
{
	if (all_alive(philo))
	{
		ft_print(philo, THINK);
		eat(philo, rsc);
	}
	return (NULL);
}

t_bool	is_odd(int id)
{
	if (id % 2 == 0)
		return (TRUE);
	return (FALSE);
}

void	lonely_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	ft_print(philo, FORK);
	pthread_mutex_unlock(philo->l_fork);
	ft_usleep(data_instance()->time_eat);
	return ;
}

/// FIXME : from here....
void	update_eating_philo_id(int id)
{
	t_mutex	*mutex_timetable;
	t_rsc	*rsc;

	rsc = rsc_instance();
	mutex_timetable = &(rsc_instance()->timetable);
	pthread_mutex_lock(mutex_timetable);
	if (id == rsc->data->last_philo_id)
		id = -1;
	rsc->who_next = &(rsc->arr_m_timetable[++id]);
	pthread_mutex_unlock(mutex_timetable);
}

void 	grab_forks(t_philo *philo)
{
//	int id;
//	t_mutex	*time_table;
	t_rsc *rsc = rsc_instance();

//	time_table = &(rsc_instance()->timetable);
//	id = philo->id;
//	while (1)
//	{
//		pthread_mutex_lock(time_table);
//		if (*(rsc_instance()->who_next) == philo->id)
//		{
//			pthread_mutex_unlock(time_table);
//			break;
//		}
//		pthread_mutex_unlock(time_table);
////		ft_usleep(CHECK_INTERVAL);
//	}

	pthread_mutex_lock(&(rsc->timetable));
	while (*(rsc->who_next) != philo->id)
	{
		pthread_mutex_unlock(&(rsc->timetable));
		ft_usleep(CHECK_INTERVAL);
		pthread_mutex_lock(&(rsc->timetable));
	}
	pthread_mutex_unlock(&(rsc->timetable));

	pthread_mutex_lock(philo->l_fork);
	ft_print(philo, FORK);
	pthread_mutex_lock(philo->r_fork);
	ft_print(philo, FORK);
	if (!all_alive(philo))
		return ;
//	if (is_odd(id)) /// odd: left -> right
//	{
//		pthread_mutex_lock(philo->l_fork);
//		ft_print(philo, FORK);
//		pthread_mutex_lock(philo->r_fork);
//		ft_print(philo, FORK);
//	}
//	else /// even: right -> left
//	{
//		pthread_mutex_lock(philo->r_fork);
//		ft_print(philo, FORK);
//		pthread_mutex_lock(philo->l_fork);
//		ft_print(philo, FORK);
//	}
}

void 	drop_forks(t_philo *philo)
{
	int id;

	if (!all_alive(philo))
		return ;
	id = philo->id;
	printf("  philo id %d, dropped fork\n", philo->id);
	if (is_odd(id))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	update_eating_philo_id(id);
//	ft_usleep(CHECK_INTERVAL);
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

void	*eat(t_philo *philo, t_rsc *rsc)
{
	if (!all_alive(philo))
		return (NULL);
//	printf("Philosopher %d is trying to grab fork\n", philo->id);
	grab_forks(philo);
//	printf("Philosopher %d has grabbed the fork\n", philo->id);
	if (!all_alive(philo))
		return (drop_forks(philo), NULL);
	ft_print(philo, EAT);
	update_last_meal(philo, rsc);
	ft_usleep(data_instance()->time_eat);

	if (!all_alive(philo))
		return (drop_forks(philo), NULL);
	update_n_eaten(philo, rsc);
//	printf("Philosopher %d is trying to drop fork\n", philo->id);
	drop_forks(philo);
//	printf("Philosopher %d has dropped fork\n", philo->id);
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