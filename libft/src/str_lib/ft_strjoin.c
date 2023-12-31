/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:52:30 by minakim           #+#    #+#             */
/*   Updated: 2023/11/23 17:31:24 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sub;
	int		i;
	int		len_1;
	int		len_2;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	sub = (char *)malloc(sizeof(char) * (len_1 + len_2 + 1));
	if (sub == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		sub[i] = s1[i];
	i = -1;
	while (s2[++i])
	{
		sub[len_1] = s2[i];
		len_1++;
	}
	sub[len_1] = '\0';
	return (sub);
}
