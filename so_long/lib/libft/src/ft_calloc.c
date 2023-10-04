/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:53:19 by minakim           #+#    #+#             */
/*   Updated: 2023/02/04 18:54:35 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*memory;
	size_t	both;

	both = nmemb * size;
	if (both / size != nmemb)
		return (NULL);
	memory = malloc(nmemb * size);
	if (!memory)
		return (NULL);
	ft_bzero(memory, nmemb * size);
	return ((void *)memory);
}
