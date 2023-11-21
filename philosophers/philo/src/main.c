/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:38:40 by minakim           #+#    #+#             */
/*   Updated: 2023/11/21 01:20:11 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_exit	philosophers(void)
{
	t_rsc	*rsc;
	t_pth	*arr_m_threads;
	t_pth	monitor;
	int		i;

	rsc = rsc_instance();
	arr_m_threads = ft_memalloc(sizeof(t_pth) * rsc->data->n_philos);
	if (!arr_m_threads)
		return (MEM_ERROR);
	pthread_create(&(monitor), NULL, death_is_sure_to_all, rsc);
	i = -1;
	while (++i < rsc->data->n_philos)
	{
		rsc->arr_m_philos[i].creation_time = ft_gettime();
		rsc->arr_m_philos[i].last_meal = ft_gettime();
		pthread_create(&(arr_m_threads[i]), NULL, lifecycle, &(rsc->arr_m_philos)[i]);
	}
	i = -1;
	while (++i < rsc->data->n_philos)
		pthread_join(arr_m_threads[i], NULL);
	free(arr_m_threads);
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	int	exit;

	exit = check_args(argc, argv);
	if (exit == SUCCESS)
		exit = init();
	if (exit == SUCCESS)
	{
		/// @TEST
		printf("time table :");
		int i = -1;
		t_rsc	*rsc = rsc_instance();
		while (++i < rsc->data->n_philos)
			printf("[%d]", rsc->arr_m_timetable[i]);
		printf("\n");

		exit = philosophers();
	}
	return (exit);
}