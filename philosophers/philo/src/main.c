/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:15:10 by minakim           #+#    #+#             */
/*   Updated: 2023/11/23 18:58:05 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_exit	exit;

	exit = check_args(argc, argv);
	if (exit == SUCCESS)
		data = init_data(argc, argv);
	if (data == NULL)
		return (ft_error_msg("init_data", MEM_ERR));

	return (0);
}