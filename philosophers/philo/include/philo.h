/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:24:22 by minakim           #+#    #+#             */
/*   Updated: 2023/10/24 15:22:46 by minakim          ###   ########.fr       */
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

/// true/false

# define TRUE 1
# define FALSE 0

/// tmp
# define NUM_STATUS_MSGS 5
typedef enum e_status
{
	none = 0,
	eating,
	jaming,
	thinking,
	death
}	t_status;


/// Boolean
typedef enum e_bool
{
	false = 0,
	true = 1
}	t_bool;

typedef struct s_philo
{
	int 			id;
	int 			n_ate;
	t_status 		s;
	size_t			t_launch;
	size_t			t_last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philo;


typedef struct s_resource
{
	int				n_philos;
	long long		time_die;
	long long		time_eat;
	long long		time_jam;
	int				required_eat;
	int				*time_table;
	t_philo			**philos;
	pthread_t		**philosophers;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*printlock[5];
	int				funeral;
	int				*next;
}					t_resource;

/* philo.c */


/* philo_routine.c */

/* philo_util.c */
int		check_valid_args(int ac, char **av);
int		ft_atoi(const char *str);
size_t	ft_get_time(void);
#endif