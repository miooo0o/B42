
#include "philo.h"

char	*print_error_type(t_errortype type)
{
	char *msg[ERRORTYPE_COUNT] = {
		"malloc",
		"Thread initialization",
		"Thread creation",
		"Philosopers init",
	};
	if (type >= 0 && type < ERRORTYPE_COUNT)
		return (msg[type]);
	else
		return ("Unknown error");
}

void	ft_error_type(t_errortype type)
{
	char *msg;

	msg = print_error_type(type);
	printf("error: %s\n", msg);
}

int	check(int result, t_errortype type)
{
	if (result == 0)
		return (0);
	ft_error_type(type);
	return (type);
}

void	ft_error_msg(const char *msg)
{
	printf("%s\n", msg);
}

void	*ft_free_till_index(void **target, int index)
{
	int	i;

	i = -1;
	while (++i < index)
	{
		free(target[i]);
		target[i] = NULL;
	}
	return (NULL);
}

void	ft_free(void *target)
{
	free(target);
	target = NULL;
}

void	ft_free_2d(void **target)
{
	int	i;

	i = -1;
	while (target[i])
	{
		free(target[i]);
		target[i] = NULL;
	}
	free(target);
}