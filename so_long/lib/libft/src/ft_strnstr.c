/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:57:09 by minakim           #+#    #+#             */
/*   Updated: 2022/12/09 17:57:15 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*little)
		return ((char *)(big));
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		if (big[i + j] == little[j])
		{
			while (big[i + j] && little[j])
			{
				if (big[i + j] != little[j] || i + j >= len)
					break ;
				j++;
			}
			if (little[j] == '\0')
				return (((char *)&big[i]));
		}
		i++;
	}
	return (NULL);
}
