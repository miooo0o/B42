/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:24:22 by minakim           #+#    #+#             */
/*   Updated: 2023/10/31 17:52:19 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

/// printlcok index enum
# define NUM_MUTEX_LOGS 2

typedef enum e_logtype
{
	log_status = 0,
	log_next_update
}	t_logtype;

/// struct
typedef struct s_philo
{
	int 			id;
	int 			n_ate;
	long long		t_creation;
	long long		t_last_meal;
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
	pthread_t		**p_threads;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*printlock[NUM_MUTEX_LOGS];
	int				funeral;
	int				*next;
}					t_resource;

/* philo.c */
void	manage_dining(void);

/* philo_init.c */
t_resource	*rsc_instance(void);

/* philo_resource.c */
t_resource	*init_rsc(int n_philo, int t_die, int t_eat, int t_jam);

/* philo_routine.c */
void	eat(t_philo *philo, t_resource *rsc);
void	jam(t_philo *philo, t_resource *rsc);
void	think(t_philo *philo, t_resource *rsc);
void	*death_occurrence(t_philo *philo);

/* philo_util.c */
int			valid_args(int ac, char **av);
long long	ft_get_time(void);
int			print_status(t_philo *philo, t_resource *rsc, char *str, int log);
void		print_dead(t_philo *philo, t_resource *rsc);
void		wait_for_turn(t_philo *philo, t_resource *rsc);
void	join_threads(t_resource	*rsc);
int			ft_error(char *s);
void	free_rsc_arr(t_resource *rsc);
void	free_resource(void);
#endif