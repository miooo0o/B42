/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:38:52 by minakim           #+#    #+#             */
/*   Updated: 2023/02/04 18:33:50 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	f_getlen(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_utoa(unsigned int nbr)
{
	char	*buf;

	if (nbr == 0)
		return (ft_strdup("0"));
	buf = (char *)malloc(sizeof(char) * f_getlen(nbr) + 1);
	buf[f_getlen(nbr)] = '\0';
	ft_get_nbr(buf, nbr, CHARSET_DEC, 10);
	return (buf);
}
