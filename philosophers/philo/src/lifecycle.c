/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:06:16 by minakim           #+#    #+#             */
/*   Updated: 2023/12/05 16:31:45 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// TODO: 테스트 후 최적화가 필요하다면, 각 필로소퍼의 상태를 업데이트하고, 우선권을 주기

void	lonely_philo(t_philo *philo)
{
	print_log(philo, THINK);
	print_log(philo, FORK);
	usleep(philo->die_us);
	print_log(philo, DIE);
}

int	should_terminate_cycle(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mx_death);
	if (philo->death_occurs || philo->is_fulled)
	{
		pthread_mutex_unlock(&philo->data->mx_death);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->data->mx_death);
	return (FALSE);
}

int grab_forks(t_philo *philo, t_fork *first, t_fork *second)
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

static void	eat(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;

	while (1)
	{
		if (ft_gettime_us() - philo->last_meal_us < philo->eat_us + philo->jam_us + INTERVAL)
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
			break;
		}
		usleep(WAIT_TURN);
	}
}

void	*ft_lifecycle(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;

	if (philo->n_philos == 1)
		return (lonely_philo(philo), NULL);
	while (!should_terminate_cycle(philo))
	{
		print_log(philo, THINK);
		eat(philo);
		print_log(philo, SLEEP);
		usleep(philo->jam_us);
	}
	return (NULL);
}
