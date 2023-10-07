/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:44:13 by minakim           #+#    #+#             */
/*   Updated: 2023/10/03 17:44:15 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memalloc(size_t size)
{
	void	*temp;

	temp = (void *)malloc(size);
	if (!temp)
		return (NULL);
	ft_bzero(temp, size);
	return (temp);
}
