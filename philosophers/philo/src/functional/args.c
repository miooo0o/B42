/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:42:36 by minakim           #+#    #+#             */
/*   Updated: 2023/11/13 15:29:46 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

t_exit	check_args(int argc, char **argv)
{
	int i;
	int exit;

	i = 0;
	if (!(argc >= 5 && argc <= 6))
		return (INPUT_VALID_ERROR);
	while (++i < argc)
	{
		exit = 0;
		if (!ft_all_satisfy(ft_isdigit, argv[i]))
			return (ft_error_msg("input should be digit only"), INPUT_VALID_ERROR);
		exit = ft_atoi(argv[i]);
		if (exit == -1)
			return (ft_error_msg("too large value"), INPUT_VALID_ERROR);
	}
	init_data(argc, argv);
	return (SUCCESS);
}
