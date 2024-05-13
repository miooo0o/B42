/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hex_low.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:47:42 by minakim           #+#    #+#             */
/*   Updated: 2023/02/04 18:33:20 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_put_hex_low(unsigned int nbr, char *charset)
{
	char			*temp;
	unsigned int	res;

	if (nbr == 0)
		return (write(1, "0", 1));
	temp = ft_put_n_char(10, '\0');
	ft_get_nbr(temp, nbr, charset, ft_strlen(charset));
	res = write(1, temp, ft_strlen(temp));
	free(temp);
	return (res);
}

// int main(void)
// {
// 	unsigned int nb = 4294967295;
// 	ft_put_hex_low(nb, CHARSET_LHEX);
// 	printf("\n%x\n", nb);
// }