/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_input_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:49:59 by minakim           #+#    #+#             */
/*   Updated: 2023/10/31 19:30:19 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo_old.h"

#define ERROR_INVALID_ARGS 0
#define ERROR_VALUE_LARGE -1
#define VALIDED_ARGS 1

int	ft_atoi_philo(const char *str)
{
	int				i;
	long long int	result;

	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result > 2147483647)
		return (ERROR_VALUE_LARGE);
	return ((int)result);
}

int	ft_isdigit(const char *s)
{
	int	i;

	if (s == NULL)
		ft_error("empty");
	i = 0;
	while (s[i] != '\0')
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (ERROR_INVALID_ARGS);
		i++;
	}
	return (VALIDED_ARGS);
}

int	check_args(int max, char **av, int val[6])
{
	int	i;

	i = 0;
	while (++i < max)
	{
		if (!ft_isdigit(av[i]))
			ft_error("non-digit value");
		val[i] = ft_atoi_philo(av[i]);
		if (val[i] == ERROR_VALUE_LARGE)
			ft_error("too large value");
	}
	return (VALIDED_ARGS);
}

int	valid_args(int ac, char **av)
{
	t_resource	*rsc;
	int			val[6];

	if (ac != 5 && ac != 6)
	{
		return (ft_error("TRY > ./philo [number_of_philosophers] [time_to_die] "
		"[time_to_eat] [time_to_sleep] [number_of_times_each_philosophers_must_eat]"));
	}
	check_args(ac, av, val);
	rsc = init_rsc(val[1], val[2], val[3], val[4]);
	if (ac == 6)
		rsc->required_eat = val[5];
	return (VALIDED_ARGS);
}

