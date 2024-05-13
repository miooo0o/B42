/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:47:43 by minakim           #+#    #+#             */
/*   Updated: 2023/01/16 17:34:15 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_int(int nbr)
{
	char	*str;
	int		res;

	str = ft_itoa(nbr);
	res = ft_put_str(str);
	free(str);
	return (res);
}
