/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:38:06 by minakim           #+#    #+#             */
/*   Updated: 2023/11/03 18:20:23 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_rsc_arr(t_resource *rsc)
{
	int	i;

	i = -1;
	while (++i < rsc->n_philos)
	{
		pthread_mutex_destroy(rsc->forks[i]);
		free(rsc->p_threads[i]);
		free(rsc->forks[i]);
		free(rsc->philos[i]);
	}
	return ;
}

void	free_resource(void)
{
	t_resource	*rsc;
	int			i;

	rsc = rsc_instance();
	free_rsc_arr(rsc);
	i = -1;
	while (++i < NUM_MUTEX_LOGS)
		pthread_mutex_destroy(rsc->printlock[i]);
	while (++i < NUM_MUTEX_LOGS)
		free(rsc->printlock[i]);
	free(rsc->philos);
	free(rsc->p_threads);
	free(rsc->forks);
	free(rsc->time_table);
	i = -1;
	return ;
}

int	ft_error(char *s)
{
	t_resource	*rsc;

	printf("error: %s.\n", s);
	rsc = rsc_instance();
	exit(1);
	return (1);
}
