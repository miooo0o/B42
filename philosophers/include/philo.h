/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:24:22 by minakim           #+#    #+#             */
/*   Updated: 2023/10/10 21:25:08 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

// Limit Loop: use addition to while condition
# define MAX_ITER	5000

// Prevent Heap mem leak: use addition to char or array
# define DATA_SIZE	3072

// Boolean
typedef enum e_bool
{
	false = 0,
	true = 1
}	t_bool;

typedef struct s_resource
{
	size_t			n_philos;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_jam;
	size_t			n_eat_opt;
	t_bool			no_deaths;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*printlock;
}					t_resource;

typedef struct s_philo
{
	size_t			id;
	size_t			n_ate;
	t_bool			is_odd;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}					t_philo;

/* philo.c */


/* philo_routine.c */
int	eat(t_philo *philo, t_resource *rsc);
int jam(t_philo *philo, t_resource *rsc);
int	think(t_philo *philo, t_resource *rsc);

/* philo_util.c */
int	check_args(int ac, char **av);

#endif