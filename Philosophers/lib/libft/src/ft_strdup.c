/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:47:44 by minakim           #+#    #+#             */
/*   Updated: 2022/12/30 22:07:56 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_s;
	size_t	slen;
	size_t	i;

	i = 0;
	slen = ft_strlen(s);
	new_s = (char *)malloc(sizeof(char) * (slen + 1));
	if (!new_s)
		return (NULL);
	while (i < slen)
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
