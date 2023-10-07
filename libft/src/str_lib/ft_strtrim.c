/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:53:03 by minakim           #+#    #+#             */
/*   Updated: 2023/02/04 18:56:54 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char const *set, char c)
{
	while (*set)
	{
		if (*set != c)
			set++;
		if (*set == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		begin;
	int		slen;
	char	*new_str;

	begin = 0;
	slen = ft_strlen(s1);
	while (check_set(set, s1[begin]) == 1 && begin < slen)
		begin++;
	while (check_set(set, s1[slen - 1]) == 1 && slen > begin)
		slen--;
	new_str = ft_substr(s1, begin, slen - begin);
	return (new_str);
}

/*
int main()
{
	char str[] = "aaaaaaaaaassadffffsmarcelaaaaaaasd"; 
	char set[] = "asd"; 
	char *p;

	printf("%s\n", str);
	p = ft_strtrim(str, set);
	printf("%s\n", p);
   
   return 0;
}*/
