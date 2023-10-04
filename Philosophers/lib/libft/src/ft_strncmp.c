/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:52:47 by minakim           #+#    #+#             */
/*   Updated: 2022/12/30 22:06:52 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && ((unsigned char)s1[i] || (unsigned char) s2[i]))
	{
		if ((unsigned char) s1[i] == (unsigned char) s2[i])
		{
			i++;
			continue ;
		}
		else if ((unsigned char) s1[i] > (unsigned char) s2[i])
			return (1);
		else if ((unsigned char) s1[i] < (unsigned char) s2[i])
			return (-1);
		i++;
	}
	if (i == n || ((unsigned char) s1[i] == '\0'
			&& (unsigned char) s2[i] == '\0'))
		return (0);
	else if ((unsigned char) s1[i] > (unsigned char) s2[i])
		return (1);
	else
		return (-1);
}
