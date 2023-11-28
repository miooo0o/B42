/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:55:39 by minakim           #+#    #+#             */
/*   Updated: 2023/11/28 16:11:19 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_err(const char *f_name, t_exit err)
{
	if (err != SUCCESS)
	{
		if (err == MEM_ERR)
			printf("error: %s: %s\n", f_name, MEM_ERROR_MSG);
		else if (err == INIT_M_ERR)
			printf("error: %s: %s\n", f_name, INIT_ERROR_MSG);
		else if (err == INPUT_VALID_ERR)
			printf("error: %s: %s\n", f_name, INPUT_VALID_ERROR_MSG);
		else if (err == GETTIME_ERR)
			printf("error: %s: %s\n", f_name, "can't get time");
		else
			printf("error: can't find error code.\n");
		return (err);
	}
	printf("error: error code not set.\n");
	return (err);
}

//void	ft_print_log(t_philo *philo, t_logs log)
//{
//	t_ll	current;
//
//	current = ft_gettime() - philo->creation_time;
//	if (log == FORK && philo->is_alive)
//		printf("%*lld %d has taken a fork\n", ALIGN, current, philo->id);
//	if (log == EAT && philo->is_alive)
//		printf("%*lld %d is eating\n", ALIGN, current, philo->id);
//	if (log == SLEEP && philo->is_alive)
//		printf("%*lld %d is sleeping\n", ALIGN, current, philo->id);
//	if (log == THINK && philo->is_alive)
//		printf("%*lld %d is thinking\n", ALIGN, current, philo->id);
//	if (log == DIE && !philo->is_alive)
//		printf("%*lld %d has died\n", ALIGN, current, philo->id);
//
//}

t_exit	destroy_arr_m_mutex(int count, t_mutex *target)
{
	int		i;

	i = -1;
	while (++i < count)
		pthread_mutex_destroy(&(target)[i]);
	free(target);
	return (SUCCESS);
}

//t_exit	init_arr_m_mutex(int count, t_mutex **target)
//{
//	int		i;
//	t_mutex	*this;
//
//	this = NULL;
//	this = ft_memalloc(sizeof(t_mutex) * count);
//	if (this == NULL)
//		return (MEM_ERR);
//	i = -1;
//	while (++i < count)
//	{
//		if (pthread_mutex_init(&this[i], NULL) != 0)
//			return (free(this), INIT_M_ERR);
//	}
//	*target = this;
//	return (SUCCESS);
//}
