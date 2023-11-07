/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:24:22 by minakim           #+#    #+#             */
/*   Updated: 2023/11/07 22:15:23 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define SET_NONE -1
# define NUM_LOCKS 5

/// printlcok index enum
typedef enum e_locktype {
	LOCK_WRITE = 0,
	LOCK_TIME_TABLE,
	LOCK_MEAL_STATE,
	LOCK_UPDATE_N_MEAL,
	LOCK_PROG_STATUS,
	LOCK_PROG_RUNNING,
}	t_locktype;

typedef enum e_mealstate {
	STATE_AWAY = 0,
	STATE_FULL /// @note finish n_time_meals
} t_mealstate;

typedef enum e_bool {
	FALSE = 0,
	TRUE,
} t_bool;

typedef enum e_status {
	STATUS_RUNNING,
	STSTUS_FINISH
} t_status;

typedef struct s_philo {
	int 			id;
	pthread_t		*thread;
	t_mealstate		meal_state;
	int				n_eat;
	t_bool 			is_eating;
	time_t			last_meal;
	time_t			creation;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}			t_philo;

typedef struct s_rsc {
	int			n_philos;
	time_t		time_die;
	time_t		time_eat;
	time_t		time_jam;
	int			required_meal;
	t_status	status;
	int			*time_table;
	int			*next;
	pthread_mutex_t	**locks;
	pthread_mutex_t	**forks;
}	t_rsc;

/// @file
t_rsc	*rsc_instance(void);
int		init_rsc(void);

/// @file
t_philo	**init_philos(t_rsc	*rsc);

/// @file utils, libft.c
int		ft_atoi(const char *str);
void	*ft_memalloc(size_t size);
int		ft_isdigit(const char c);
int		ft_isspace(const char c);
int		ft_all_satisfy(int (*f)(char c), char *s);

/// @file utils, utils.c
pthread_mutex_t	**init_mutexes(int count);
time_t			get_time(void);
void			print_msg(t_philo *philo, char *msg);

/// @file utils, error.c
int	ft_error_msg(const char *msg);

/// @file utils, free.c
void	*ft_free_till_index(void **target, int index);
void	ft_free(void *target);
void	ft_free_2d(void **target);

/// @file functional, vaild_input.c
int valid_args(int argc, char **argv);

void	*monitor(void *ptr);

int	is_running(t_rsc *rsc, t_philo *philo);
int	philosopers(t_philo **philos);

int	ft_usleep(time_t time);
#endif