/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:06:16 by minakim           #+#    #+#             */
/*   Updated: 2023/11/30 17:25:56 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int lonely_philo(t_philo *philo)
{
	t_ll	current;
	t_bool	is_lonely;

	pthread_mutex_lock(&philo->data->mx_death);
	current = ft_gettime_us() - philo->creation_us;
	if (!philo->death_occurs && philo->l_fork == NULL)
	{
		printf("%*lld %d has taken a fork\n", ALIGN, current, philo->id);
		is_lonely = TRUE;
	}
	pthread_mutex_unlock(&philo->data->mx_death);
	return (is_lonely);
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

static void	eat_odd(t_philo *philo)
{

	if (ft_gettime_us() - philo->last_meal_us < philo->eat_us + philo->jam_us + INTERVAL)
		usleep(JAM);
	pthread_mutex_lock(philo->r_fork);
	print_log(philo, FORK);
	pthread_mutex_lock(philo->l_fork);
	print_log(philo, FORK);
	pthread_mutex_lock(&philo->mx_meal);
	philo->last_meal_us = ft_gettime_us();
	philo->left_meal--;
	if (!philo->left_meal)
		philo->is_fulled = TRUE;
	print_log(philo, EAT);
	ft_usleep_us(philo->eat_us);
	pthread_mutex_unlock(&philo->mx_meal);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);

}

static void	eat_even(t_philo *philo)
{
	if (ft_gettime_us() - philo->last_meal_us < philo->eat_us + philo->jam_us + INTERVAL)
		usleep(JAM);
	pthread_mutex_lock(philo->l_fork);
	print_log(philo, FORK);
	pthread_mutex_lock(philo->r_fork);
	print_log(philo, FORK);
	pthread_mutex_lock(&philo->mx_meal);
	philo->last_meal_us = ft_gettime_us();
	philo->left_meal--;
	if (!philo->left_meal)
		philo->is_fulled = TRUE;
	print_log(philo, EAT);
	ft_usleep_us(philo->eat_us);
	pthread_mutex_unlock(&philo->mx_meal);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*ft_lifecycle(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (lonely_philo(philo))
		return (NULL);
	while (1)
	{
		if (should_terminate_cycle(philo))
			break;
		print_log(philo, THINK);
		if (philo->id % 2 == 0)
			eat_even(philo);
		else
			eat_odd(philo);
		print_log(philo, SLEEP);
		usleep(philo->jam_us);
	}
	return (NULL);
}