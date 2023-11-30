/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:27:42 by minakim           #+#    #+#             */
/*   Updated: 2023/11/30 16:30:50 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_perror(const char *msg)
{
	write(STDERR_FILENO, "error :", 7);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}

t_ll	ft_gettime_us(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ft_perror("gettimeofday"), EXIT_FAILURE);
	return (tv.tv_sec * 1000000LL + tv.tv_usec);
}

void	ft_usleep_us(t_ll duration_usec)
{
	t_ll	start_time;

	start_time = ft_gettime_us();
	while (ft_gettime_us() - start_time < duration_usec)
		;
}

void	print_log(t_philo *philo, t_logs type)
{
	t_ll	current;

	current = (ft_gettime_us() - philo->creation_us) / 1000;
	pthread_mutex_lock(&philo->data->mx_log);
	pthread_mutex_lock(&philo->data->mx_death);
	if (!philo->death_occurs)
	{
		if (type == FORK)
			printf("%*lld %d has taken a fork\n", ALIGN, current, philo->id);
		else if (type == EAT)
			printf("%*lld %d is eating\n", ALIGN, current, philo->id);
		else if (type == SLEEP)
			printf("%*lld %d is sleeping\n", ALIGN, current, philo->id);
		else if (type == THINK)
			printf("%*lld %d is thinking\n", ALIGN, current, philo->id);
		else if (type == DIE)
			printf("%*lld %d has died\n", ALIGN, current, philo->id);
	}
	pthread_mutex_unlock(&philo->data->mx_death);
	pthread_mutex_unlock(&philo->data->mx_log);
}