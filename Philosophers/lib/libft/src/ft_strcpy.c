/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi■■■■■ <mi■■■■■@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:30:31 by mi■■■■■           #+#    #+#             */
/*   Updated: 2023/04/30 18:30:40 by mi■■■■■          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcpy(char *dest, const char *src)
{
	size_t	i;
	size_t	slen;

	i = 0;
	slen = ft_strlen(src);
	if (!dest || !src)
		return (0);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (slen);
}
