/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dining.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:48:49 by minakim           #+#    #+#             */
/*   Updated: 2023/11/06 20:19:23 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	*lifecycle(t_philo *philo)
{
	t_resource	*rsc;
	pthread_mutex_t	* hold;

	rsc = rsc_instance();
	hold = rsc->m_lock[L_HOLD];

	if (rsc->n_philos == 1)
		return (death_occurrence(philo));
	pthread_mutex_lock(rsc->m_lock[L_START]);
	pthread_mutex_unlock(rsc->m_lock[L_START]);
	while (!rsc->funeral)
	{
		if (philo->id != *(rsc->next))
		{
			usleep(10);
			continue ;
		}
		eat(philo, rsc);
		pthread_mutex_lock(hold);
		if (philo->n_ate == rsc->required_eat)
		{
			pthread_mutex_unlock(hold);
			break ;
		}
		pthread_mutex_unlock(hold);
		jam(philo, rsc);
		think(philo, rsc);
	}
	return (0);
}

int	prepare_dining_table(t_resource *rsc)
{
	int	i;

	i = -1;
	while (++i < rsc->n_philos)
	{
		rsc->philos[i]->t_creation = ft_get_time();
		rsc->philos[i]->t_last_meal = rsc->philos[i]->t_creation;
		if (pthread_create(rsc->p_threads[i], NULL,
						   (void *) lifecycle, rsc->philos[i]))
			return (0);
	}
	return (1);
}

int	status_check(t_resource *rsc)
{
	int				i;
	long long		time_since_last_meal;
	pthread_mutex_t	*printlock;

	printlock = rsc->m_lock[L_PRINT];
	pthread_mutex_lock(printlock);
	i = -1;
	while (++i < rsc->n_philos)
	{
		time_since_last_meal = ft_get_time() - rsc->philos[i]->t_last_meal;
		if (time_since_last_meal > rsc->time_die)
		{
			print_dead(rsc->philos[i], rsc);
			pthread_mutex_unlock(printlock);
			return (0);
		}
	}
	pthread_mutex_unlock(printlock);
	return (1);
}

void	manage_dining(void)
{
	t_resource	*rsc;

	rsc = rsc_instance();
	if (!prepare_dining_table(rsc))
		ft_error("fail to prepare dining");
	/// while loop (philos alive)

	while (!rsc->funeral && rsc->required_eat < 0)
	{
		status_check(rsc);
		usleep(100);
	}
	/// Join threads here
	join_threads(rsc);
	/// Free resources here
	free_resource();
	return ;
}
