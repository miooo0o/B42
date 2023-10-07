/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 17:27:25 by minakim           #+#    #+#             */
/*   Updated: 2022/12/10 17:27:28 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			ni;
	char			*str;

	i = 0;
	ni = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[i] != '\0' && s[i])
	{
		if (i >= start && ni < len)
			str[ni++] = s[i];
		i++;
	}
	str[ni] = '\0';
	return (str);
}
