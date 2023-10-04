/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:52:07 by minakim           #+#    #+#             */
/*   Updated: 2023/07/13 20:03:38 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_count(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (i == 0)
		{
			if (s[i] != c)
				count++;
		}
		else
		{
			if (s[i] != c && s[i - 1] == c)
				count++;
		}
		i++;
	}
	return (count);
}

char	**do_split(char const *s, char c, char **split)
{
	size_t	start;
	size_t	index;
	size_t	split_index;

	index = 0;
	split_index = 0;
	while (s[index])
	{
		if (s[index] != c)
		{
			start = index;
			while (s[index] != c && s[index])
				index++;
			split[split_index++] = ft_substr(s, start, index - start);
		}
		else
			index++;
	}
	split[split_index] = NULL;
	return (split);
}

int	is_contains_trigger(char const *str, char trigger)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == trigger)
			return (1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**split;

	if (ft_isprint(c))
	{
		is_contains_trigger(s, c);
		count = get_count(s, c);
		split = (char **) malloc(sizeof(char *) * (count + 1));
		if (!s || !split)
			return (0);
		split = do_split(s, c, split);
		return (split);
	}
	return (NULL);
}
