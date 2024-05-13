/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:47:06 by minakim           #+#    #+#             */
/*   Updated: 2022/12/21 12:59:17 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long	number;
	long	sign;
	size_t	i;

	number = 0;
	sign = 1;
	i = 0;
	while ((str[i] != '\0') && ft_check(str[i]) == 1)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while ((str[i] >= '0' && str[i] <= '9') && (str[i] != '\0'))
	{
		number = (number * 10) + (str[i] - 48);
		if (number > 2147483647 && sign == 1)
			return (-1);
		if (number > 2147483648 && sign == -1)
			return (0);
		i++;
	}
	return (number * sign);
}
