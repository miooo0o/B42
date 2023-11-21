/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:16:23 by minakim           #+#    #+#             */
/*   Updated: 2023/11/21 18:33:19 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error_msg(const char *msg)
{
	printf("error: %s\n", msg);
	return (-1);
}

t_exit	destroy_arr_m_mutex(int count, t_mutex *target)
{
	int		i;

	i = -1;
	while (++i < count)
		pthread_mutex_destroy(&(target)[i]);
	free(target);
	return (SUCCESS);
}