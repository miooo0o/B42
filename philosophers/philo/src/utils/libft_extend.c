/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:28:26 by minakim           #+#    #+#             */
/*   Updated: 2023/12/05 16:31:37 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_memalloc(size_t size)
{
	void	*temp;

	temp = (void *)malloc(size);
	if (!temp)
		return (NULL);
	memset(temp, 0, size);
	return (temp);
}

/// @note work with ft_is functions
int ft_all_satisfy(int (*f)(char c), char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (!f(*s))
			return (0);
		s++;
	}
	return (1);
}
