/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vaild_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:55:05 by minakim           #+#    #+#             */
/*   Updated: 2023/11/04 18:55:05 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo_2.h"

#define ERROR_VALUE_LARGE -1

void	init_time_table(t_config *conf, int n_philo)
{
	int	i;
	int	ph_id;

	i = -1;
	ph_id = 0;
	while (ph_id < n_philo)
	{
		conf->time_table[++i] = ph_id;
		ph_id += 2;
	}
	ph_id = 1;
	while (ph_id < n_philo)
	{
		conf->time_table[++i] = ph_id;
		ph_id += 2;
	}
	return ;
}


int check_args(int max, char **av, int val[5])
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (++i < max)
	{
		if (!ft_all_satisfy(ft_isdigit, av[i]))
			return (ft_error_msg("input should be digit only"), 0);
		val[j] = ft_atoi(av[i]);
		if (val[j] == ERROR_VALUE_LARGE)
			return (ft_error_msg("too large value"), 0);
		j++;
	}
	return (1);
}


pthread_mutex_t	**init_mutexes(int count)
{
	int i;
	pthread_mutex_t	**target;

	target = ft_memalloc(sizeof(pthread_mutex_t *) * count);
	if (target == NULL)
		return (ft_error_type(ERROR_MALLOC), NULL);
	i = -1;
	while (++i < count)
	{
		target[i] = ft_memalloc(sizeof(pthread_mutex_t));
		if (target[i] == NULL)
			return (ft_error_type(ERROR_MALLOC), NULL);
		else if (check(pthread_mutex_init(target[i], NULL), ERROR_THREAD_INIT) != 0)
			return (NULL);
	}
	return (target);
}

t_config	*conf_instance(void)
{
	static t_config	this;
	static int			is_init;

	if (is_init)
		return (&this);
	this = (t_config){
	.n_philos = 0,
	.time_die = 0,
	.time_eat = 0,
	.time_jam = 0,
	.required_eat = 0,
	.death_occurs = NONE,
	.forks = NULL,
	.locks = NULL,
	};
	is_init = 1;
	return (&this);
}


t_config	*init_handler(const int ac, const int val[5])
{
	t_config	*conf;

	conf = conf_instance();
	if (!conf)
		return (NULL);
	conf->n_philos = val[0];
	conf->time_die = val[1];
	conf->time_eat = val[2];
	conf->time_jam = val[3];
	if (ac == 6)
		conf->required_eat = val[4];
	/// init mutex @note 아직 뮤텍스 함수 완료하지 못함.
	conf->time_table = (int *)ft_memalloc(sizeof(int) * conf->n_philos);
	init_time_table(conf, conf->n_philos);
	conf->next = &conf->time_table[0];
	conf->forks = init_mutexes(conf->n_philos);
	conf->locks = init_mutexes(LOCKTYPE_COUNT);
	if (conf->forks == NULL || conf->locks == NULL)
		return (NULL);
	return (conf);
}

t_config	*config_from_args(int ac, char **av)
{
	int			val[5];
	t_config	*conf;

	conf = NULL;
	if (ac != 5 && ac != 6)
	{
		return(ft_error_msg("TRY > ./philo [number_of_philosophers] [time_to_die] "
						 "[time_to_eat] [time_to_sleep]"
						 "[number_of_times_each_philosophers_must_eat]"), NULL);
	}
	if (check_args(ac, av, val))
		conf = init_handler(ac, val);
	return (conf);
}