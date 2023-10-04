/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_n_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:40:46 by minakim           #+#    #+#             */
/*   Updated: 2023/02/04 18:33:31 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_put_n_char(int n, char c)
{
	char	*buffer;
	int		i;

	buffer = (char *)malloc(n + 1);
	if (!buffer)
		return (NULL);
	i = 0;
	while (i < n)
	{
		buffer[i] = c;
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}
