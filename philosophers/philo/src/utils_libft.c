/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:56:55 by minakim           #+#    #+#             */
/*   Updated: 2023/11/23 17:56:55 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

int	ft_isdigit(char c)
{
	if (!(c >= '0' && c <= '9'))
		return (0);
	return (1);
}

/// @note philo
int	ft_atoi(const char *str)
{
	long long int	result;

	result = 0;
	while (ft_isspace(*str))
		str++;
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (result > 2147483647)
		return (-1);
	return ((int)result);
}

void	*ft_memalloc(size_t size)
{
	void	*temp;

	temp = (void *)malloc(size);
	if (!temp)
		return (NULL);
	memset(temp, 0, size);
	return (temp);
}

/// @note work with ft_is functions
int ft_all_satisfy(int (*f)(char c), char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (!f(*s))
			return (0);
		s++;
	}
	return (1);
}
