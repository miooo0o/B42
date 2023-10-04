/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:51:18 by minakim           #+#    #+#             */
/*   Updated: 2022/12/30 22:08:41 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (n == 0 || dest == src)
		return (dest);
	if (dest == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (n-- > 0)
	{
		*d = *s;
		d++;
		s++;
	}
	return (dest);
}
