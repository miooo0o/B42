/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi■■■■■ <mi■■■■■@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:53:19 by mi■■■■■           #+#    #+#             */
/*   Updated: 2023/04/30 18:47:27 by mi■■■■■          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	char	*memory;
	size_t	total_size;

	total_size = num_elements * element_size;
	if (total_size / element_size != num_elements)
		return (NULL);
	memory = malloc(num_elements * element_size);
	if (!memory)
		return (NULL);
	ft_bzero(memory, num_elements * element_size);
	return ((void *)memory);
}
