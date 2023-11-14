/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:43:51 by minakim           #+#    #+#             */
/*   Updated: 2023/11/14 17:43:19 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	a_sudden_death_is_the_best(t_rsc *rsc, int target)
{
	int		i;

	i = -1;
	while (++i < rsc->data->n_philos)
	{
		pthread_mutex_lock(&rsc->arr_m_status[i]);
		rsc->arr_m_philos[i].is_alive = FALSE;
		pthread_mutex_unlock(&rsc->arr_m_status[i]);
	}
	ft_print(&rsc->arr_m_philos[target], DIE);
}


int detecting_target(t_rsc *rsc)
{
	int i;
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
	return (NONE_SET);
}


void	*death_is_sure_to_all(void	*r)
{
	t_rsc	*rsc;
	int		who_died;

	rsc = r;
	while (1)
	{
		who_died = detecting_target(rsc);
		if (who_died != NONE_SET)
		{
			a_sudden_death_is_the_best(rsc, who_died);
			break ;
		}
	}
	ft_usleep(1000);
	return (NULL);
}