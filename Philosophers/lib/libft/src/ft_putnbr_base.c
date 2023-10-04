/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi■■■■■ <mi■■■■■@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:29:27 by mi■■■■■           #+#    #+#             */
/*   Updated: 2023/04/30 18:30:22 by mi■■■■■          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_get_nbr(char *buf, unsigned int nbr, \
					const char *base, const unsigned int num_base)
{
	unsigned int	digit;
	unsigned int	i;

	if (nbr == 0)
		return (0);
	digit = nbr % num_base;
	i = ft_get_nbr(buf, nbr / num_base, base, num_base);
	buf[i] = base[digit];
	return (i + 1);
}

unsigned int	ft_putnbr_base(unsigned int nbr, const char *base, int fd)
{
	char			temp[33];
	unsigned int	res;
	unsigned int	num_base;

	if (nbr == 0)
		return (write(fd, "0", 1));
	if (base[0] == '\0' || base[1] == '\0')
		return (-1);
	num_base = ft_strlen(base);
	ft_get_nbr(temp, nbr, base, num_base);
	res = write(fd, temp, ft_strlen(temp));
	return (res);
}
