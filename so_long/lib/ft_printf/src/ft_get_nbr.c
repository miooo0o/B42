/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_nbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:00:08 by minakim           #+#    #+#             */
/*   Updated: 2023/02/04 18:33:17 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_get_nbr(char *buf, unsigned int nbr, \
					char *charset, int len_base)
{
	unsigned int	digit;
	unsigned int	i;

	if (nbr == 0)
		return (0);
	digit = nbr % len_base;
	i = ft_get_nbr(buf, nbr / len_base, charset, len_base);
	buf[i] = charset[digit];
	return (i + 1);
}
