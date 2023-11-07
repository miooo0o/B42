/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:36:48 by minakim           #+#    #+#             */
/*   Updated: 2023/11/06 19:43:46 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (ft_error("gettimeofday fail"), -1);
	return ((long long)time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	print_status(t_philo *philo, t_resource *rsc, char *str, int log)
{
	long long	now;

	now = 0;
	pthread_mutex_lock(rsc->m_lock[log]);
	if (!rsc->funeral)
	{
		now = ft_get_time() - philo->t_creation;
		printf("%lld %u %s\n", now, philo->id + 1, str);
	}
	pthread_mutex_unlock(rsc->m_lock[log]);
	return ((int)now);
}

void	print_dead(t_philo *philo, t_resource *rsc)
{
	if (rsc->funeral != 1)
	{
		rsc->funeral = 1;
		printf("%lld %u %s\n", ft_get_time() - philo->t_creation, \
				philo->id + 1, "died");
		usleep(1000);
	}
}

void	wait_for_turn(t_philo *philo, t_resource *rsc)
{
	while (philo->id != *(rsc->next))
		usleep(10);
}

void	join_threads(t_resource	*rsc)
{
	int i;

	i = -1;
	while (++i < rsc->n_philos)
		pthread_join(*(rsc->p_threads[i]), NULL);
}

int	ft_isdigit(const char c)
{
	if (!(c >= '0' && c <= '9'))
		return (0);
	return (1);
}

/// @note work with ft_is functions
int ft_all_satisfy(int (*f)(char c), char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (!f(*s))
			return (0);
		s++;
	}
	return (1);
}

int	ft_error(const char *msg)
{
	printf("%s\n", msg);
	return (0);
}