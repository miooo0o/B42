/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:36:48 by minakim           #+#    #+#             */
/*   Updated: 2023/10/23 17:15:05 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

int	is_correct_args(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '\0')
	{
		if (av[i] < '0' || av[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_valid_args(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (ft_atoi(av[1]) < 1 || !is_correct_args(av[1]))
			return (printf("Number_of_philosophers must be at least 1.\n"));
		if (ft_atoi(av[2]) < 1 || !is_correct_args(av[2]))
			return (printf("Time_to_die must be at least 1.\n"));
		if (ft_atoi(av[3]) < 1 || !is_correct_args(av[3]))
			return (printf("Time_to_eat must be at least 1.\n"));
		if (ft_atoi(av[4]) < 1 || !is_correct_args(av[4]))
			return (printf("Time_to_sleep must be at least 1.\n"));
		if (av[5] && ft_atoi(av[5]) < 1 || !is_correct_args(av[5]))
			return (printf("Number_of_times_each_philosopher_must_eat \
must be at least 1.\n"));
	}
	else
	{
		printf("TRY > ./philo [number_of_philosophers] ");
		printf("[time_to_die] [time_to_eat] [time_to_sleep]\n");
		printf("(Optional) [number_of_times_each_philosophers_must_eat]\n");
		return (1);
	}
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
