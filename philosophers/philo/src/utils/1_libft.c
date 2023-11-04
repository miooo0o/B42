
#include "philo.h"

#define ERROR_VALUE_LARGE -1

int	ft_isspace(const char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

int	ft_isdigit(const char c)
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
		result *= 10 + (*str - '0');
		str++;
	}
	if (result > 2147483647)
		return (ERROR_VALUE_LARGE);
	return ((int)result);
}

int	ft_error(char *s)
{
	printf("error: %s.\n", s);
	exit(1);
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