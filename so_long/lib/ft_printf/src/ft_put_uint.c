/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_uint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:40:30 by minakim           #+#    #+#             */
/*   Updated: 2023/02/04 18:33:44 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_put_uint(unsigned int nbr)
{
	char	*str;
	int		res;

	str = ft_utoa(nbr);
	res = ft_put_str(str);
	free(str);
	return (res);
}
