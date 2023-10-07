/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:44:35 by minakim           #+#    #+#             */
/*   Updated: 2023/10/07 12:08:37 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *str, const char *charset);

/// @brief Calculates the length of the initial segment of a string that does
/// NOT match with characters from a specified set.
/// @param str  The string to be examined.
/// @param charset The set of characters to be used as stopper.
/// @return The length of the initial segment of 'str'
/// that NOT match any character in 'charset'.
size_t	ft_strcspn(const char *str, const char *charset)
{
	size_t	initial_length;
	size_t	i;
	size_t	j;

	initial_length = 0;
	i = -1;
	while (++i < ft_strlen(str))
	{
		j = -1;
		while (++j < ft_strlen(charset))
		{
			if (charset[j] == str[i])
				return (i);
		}
		initial_length++;
	}
	return (initial_length);
}
// #include <stdio.h>
// int main(void)
// {
// 	//test : ft_strcspn
// 	char string[] = "here is test functions";
// 	char digit[] = " heristfn";

// 	size_t length = ft_strcspn(string, digit);
// 	printf("%d\n", (int)length);
// 	length = strcspn(string, digit);
// 	printf("%d\n", (int)length);
// }
