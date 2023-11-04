/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vaild_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:55:05 by minakim           #+#    #+#             */
/*   Updated: 2023/11/04 18:55:05 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define ERROR_VALUE_LARGE -1

int check_args(int max, char **av, int val[6])
{
	int	i;
	int j;
	char	*s;

	s = NULL;
	i = 0;
	j = 0;
	while (++i < max)
	{
		if (!ft_all_satisfy(ft_isdigit, s))
			ft_error("input should be digit only");
		val[i] = ft_atoi(av[i]);
		if (val[i] == ERROR_VALUE_LARGE)
			ft_error("too large value");
	}
	return (1);
}

int	valid_args(int ac, char **av)
{
	int			val[6];


	if (ac != 5 && ac != 6)
	{
		return (ft_error("TRY > ./philo [number_of_philosophers] [time_to_die] "
						 "[time_to_eat] [time_to_sleep] [number_of_times_each_philosophers_must_eat]"));
	}
	check_args(ac, av, val);
//	if (ac == 6)
//		rsc->required_eat = val[5];
}