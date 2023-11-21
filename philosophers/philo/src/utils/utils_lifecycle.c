/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:19:52 by minakim           #+#    #+#             */
/*   Updated: 2023/11/20 22:15:51 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	all_alive(t_philo *philo)
{
	t_rsc	*rsc;

	rsc = rsc_instance();
	pthread_mutex_lock(&(rsc->arr_m_status[philo->id]));
	if (philo->is_alive == TRUE)
	{
		pthread_mutex_unlock(&(rsc->arr_m_status[philo->id]));
		return (TRUE);
	}
	pthread_mutex_unlock(&(rsc->arr_m_status[philo->id]));
	return (FALSE);
}