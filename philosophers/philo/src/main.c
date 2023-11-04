/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:08:31 by minakim           #+#    #+#             */
/*   Updated: 2023/11/04 19:15:04 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	manage_dining(void)
{

}

int	main(int ac, char **av)
{
	t_resource	*rsc;
	t_philo		*per;
	if (!valid_args(ac, av))
		return (1);
	if (!manage_dining())
	{
		return (1);
	}
	return (0);
}