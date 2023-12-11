/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:00:03 by minakim           #+#    #+#             */
/*   Updated: 2023/12/11 16:08:36 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			grab_forks(t_philo *philo, t_fork *first, t_fork *second);
static void	find_order_to_grab(t_philo *philo, t_fork **first, t_fork **second);
static void	release_forks(t_fork *first, t_fork *second, t_philo *philo);

int	hungry(t_philo *philo)
{
	t_ll	from_last_us;

	pthread_mutex_lock(&philo->mx_state);
	if (philo->state == NONE_SET)
	{
		philo->state = EATING;
		pthread_mutex_unlock(&philo->mx_state);
		return (TRUE);
	}
	if (philo->state == NORMAL_HUNGRY)
	{
		from_last_us = ft_gettime_us() - philo->last_meal_us;
		if (from_last_us <= philo->urgent_us)
			philo->state = SEVERELY_HUNGRY;
	}
	if (philo->state == SEVERELY_HUNGRY)
	{
		pthread_mutex_unlock(&philo->mx_state);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->mx_state);
	return (FALSE);
}

void	eat(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;

	while (1)
	{
		if (!hungry(philo))
			usleep(philo->urgent_us);
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
			release_forks(first, second, philo);
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

static void	release_forks(t_fork *first, t_fork *second, t_philo *philo)
{
	second->is_taken = FALSE;
	pthread_mutex_unlock(second->mx);
	first->is_taken = FALSE;
	pthread_mutex_unlock(first->mx);
	pthread_mutex_lock(&philo->mx_state);
	philo->state = NORMAL_HUNGRY;
	pthread_mutex_unlock(&philo->mx_state);
}

