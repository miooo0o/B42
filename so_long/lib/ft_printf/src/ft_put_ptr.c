/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:52:36 by minakim           #+#    #+#             */
/*   Updated: 2023/02/04 18:33:36 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_get_hex_ptr(char *buf, unsigned long nbr, \
					char *charset, int len_base)
{
	unsigned long	digit;
	unsigned int	i;

	if (nbr == 0)
		return (0);
	digit = nbr % len_base;
	i = ft_get_hex_ptr(buf, nbr / len_base, charset, len_base);
	buf[i] = charset[digit];
	return (i + 1);
}

int	ft_put_ptr(unsigned long ptr)
{
	char			*buf;
	unsigned long	nbr;
	int				res;

	nbr = ptr;
	if (ptr == 0)
		return (write(1, "(nil)", 5));
	buf = ft_put_n_char(16, '\0');
	ft_get_hex_ptr(buf, nbr, CHARSET_LHEX, ft_strlen(CHARSET_LHEX));
	res = ft_put_str("0x");
	res += ft_put_str(buf);
	free(buf);
	return (res);
}
