/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi■■■■■ <mi■■■■■@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:53:00 by minakim           #+#    #+#             */
/*   Updated: 2023/05/02 19:11:58 by mi■■■■■          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	slen;

	i = 0;
	slen = ft_strlen(src);
	if (!dest || !src)
		return (0);
	if (size == 0)
		return (slen);
	while (src[i] != '\0' && i + 1 < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (slen);
}
