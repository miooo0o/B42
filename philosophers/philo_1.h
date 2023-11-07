/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:24:22 by minakim           #+#    #+#             */
/*   Updated: 2023/11/06 20:18:24 by minakim          ###   ########.fr       */
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
# define NUM_MUTEX_LOGS 7

#define ERROR_VALUE_LARGE -1

typedef enum e_locktype
{
	L_PRINT = 0,
	L_NEXT_UPDATE,
	L_MEAL,
	L_HOLD,
	L_TIME,
	L_START
}	t_locktype;

/// struct
typedef struct s_philo
{
	int 			id;
	int 			num_type;
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
	pthread_mutex_t **m_lock;
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
int			config_handler_from_args(int ac, char **av);
time_t	ft_get_time(void);
int			print_status(t_philo *philo, t_resource *rsc, char *str, int log);
void		print_dead(t_philo *philo, t_resource *rsc);
void		wait_for_turn(t_philo *philo, t_resource *rsc);
void	join_threads(t_resource	*rsc);
int	ft_error(const char *msg);
void	free_rsc_arr(t_resource *rsc);
void	free_resource(void);

int	ft_isdigit(const char c);
/// @note work with ft_is functions
int ft_all_satisfy(int (*f)(char c), char *s);
int	valid_args(int ac, char **av);
#endif