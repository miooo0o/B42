#include "philo.h"

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