/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:43:51 by minakim           #+#    #+#             */
/*   Updated: 2023/11/21 18:49:28 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo_4.h"

void	a_sudden_death_is_the_best(t_rsc *rsc, int id)
{
	int		i;

	i = -1;
	printf("dead philo found\n");
	while (++i < rsc->data->n_philos)
	{
		pthread_mutex_lock(&rsc->arr_m_status[i]);
		rsc->arr_m_philos[i].is_alive = FALSE;
		pthread_mutex_unlock(&rsc->arr_m_status[i]);
	}
	if (id >= 0)
		ft_print(&rsc->arr_m_philos[id], DIE);
}

int who_died(t_rsc *rsc)
{
	int		i;
	t_ll	current;
	t_ll	passed_time;

	current = ft_gettime();
	i = -1;
	while (++i < rsc->data->n_philos)
	{
		passed_time = current - rsc->arr_m_philos[i].last_meal;
		if (passed_time > rsc->data->time_die)
			return (i);
	}
	return (NONE);
}

//int all_n_eaten(t_rsc *rsc)
//{
//
//	return (TRUE);
//	return (FALSE);
//}

void	*death_is_sure_to_all(void	*p)
{
	t_rsc	*rsc;
	int		the_philo;

	rsc = p;
	while (1)
	{
		the_philo = who_died(rsc);
		if (the_philo != NONE)
		{
			a_sudden_death_is_the_best(rsc, the_philo);
			break ;
		}
//		if (rsc->data->required_n_meals >= 0 && all_n_eaten(rsc))
//		{
//			a_sudden_death_is_the_best(rsc, NONE);
//			break ;
//		}

	}
//	ft_usleep(1);
	return (NULL);
}