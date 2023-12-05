/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:00:03 by minakim           #+#    #+#             */
/*   Updated: 2023/12/05 17:06:56 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			grab_forks(t_philo *philo, t_fork *first, t_fork *second);
static void	find_order_to_grab(t_philo *philo, t_fork **first, t_fork **second);
static void	release_forks(t_fork *first, t_fork *second);

void	eat(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;

	while (1)
	{
		if (ft_gettime_us() - philo->last_meal_us < \
			philo->eat_us + philo->jam_us + INTERVAL)
			usleep(WAIT_TURN);
		find_order_to_grab(philo, &first, &second);
		if (grab_forks(philo, first, second))
		{
			pthread_mutex_lock(&philo->mx_meal);
			philo->last_meal_us = ft_gettime_us();
			philo->left_meal--;
			if (!philo->left_meal)
				philo->is_fulled = TRUE;
			print_log(philo, EAT);
			ft_usleep_us(philo->eat_us);
			pthread_mutex_unlock(&philo->mx_meal);
			release_forks(first, second);
			break ;
		}
		usleep(WAIT_TURN);
	}
}

int	grab_forks(t_philo *philo, t_fork *first, t_fork *second)
{
	pthread_mutex_lock(first->mx);
	if (!first->is_taken)
	{
		first->is_taken = TRUE;
		pthread_mutex_lock(second->mx);
		if (!second->is_taken)
		{
			second->is_taken = TRUE;
			print_log(philo, FORK);
			print_log(philo, FORK);
			return (TRUE);
		}
		else
		{
			pthread_mutex_unlock(second->mx);
			pthread_mutex_unlock(first->mx);
			return (FALSE);
		}
	}
	else
		pthread_mutex_unlock(first->mx);
	return (FALSE);
}

static void	find_order_to_grab(t_philo *philo, t_fork **first, t_fork **second)
{
	*first = NULL;
	*second = NULL;
	if (philo->id % 2 == 0)
	{
		*first = &philo->l_fork;
		*second = &philo->r_fork;
	}
	else
	{
		*first = &philo->r_fork;
		*second = &philo->l_fork;
	}
}

static void	release_forks(t_fork *first, t_fork *second)
{
	second->is_taken = FALSE;
	pthread_mutex_unlock(second->mx);
	first->is_taken = FALSE;
	pthread_mutex_unlock(first->mx);
}
