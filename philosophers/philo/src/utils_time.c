/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:52:28 by minakim           #+#    #+#             */
/*   Updated: 2023/11/28 15:49:00 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @list functions
t_ll	ft_gettime(t_philo *philo, t_sec mode);
t_ll	current_time_ms(void);
t_ll	current_time_usec(void);
t_ll	ms_to_usec(t_ll	milli);
t_ll	usec_to_ms(t_ll micro);

t_ll	ft_gettime(t_philo *philo, t_sec mode)
{
	struct timeval	tv;
	t_ll			time;

	pthread_mutex_lock(&philo->data->m_time);
	time = 0;
	if (gettimeofday(&tv, NULL))
		return (ft_err("gettimeofday", GETTIME_ERR));
	if (mode == GET_USEC)
		time = current_time_usec();
	else if (mode == GET_MS)
		time = current_time_ms();
	else
	{
		pthread_mutex_unlock(&philo->data->m_time);
		return (ft_err("mode", GETTIME_ERR));
	}
	pthread_mutex_unlock(&philo->data->m_time);
	return (time);
}

t_ll	current_time_ms(void)
{
	struct timeval	tv;
	t_ll			millisecs;

	gettimeofday(&tv, NULL);
	millisecs = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (millisecs);
}

t_ll	current_time_usec(void)
{
	struct timeval	tv;
	t_ll			microsecs;

	gettimeofday(&tv, NULL);
	microsecs = tv.tv_sec * 1000000LL + tv.tv_usec;
	return (microsecs);
}

t_ll	ms_to_usec(t_ll	milli)
{
	return (milli * 1000);
}

t_ll	usec_to_ms(t_ll micro)
{
	return (micro / 1000);
}
