/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:08:58 by minakim           #+#    #+#             */
/*   Updated: 2023/12/05 17:08:19 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (ft_perror(EINARGNUM), EXIT_FAILURE);
	if (!check_args(ac, av))
		return (ft_perror(EINVAL), EXIT_FAILURE);
	if (!init_data(ac, av, &data))
		return (ft_perror(ENOMEM), EXIT_FAILURE);
	if (!philosophers(&data))
		return (EXIT_FAILURE);
	write(STDOUT_FILENO, "\nThe program terminated successfully.\n", 38);
	return (EXIT_SUCCESS);
}
