/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:24:22 by minakim           #+#    #+#             */
/*   Updated: 2023/11/08 00:05:40 by minakim          ###   ########.fr       */
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

typedef enum e_bool{
	FALSE = 0,
	TRUE
}	t_bool;

typedef enum e_mealstate {
	STATE_AWAY = 0,
	STATE_FULL /// @note finish n_time_meals
} t_mealstate;

typedef enum e_status {
	NONE = 0,
	EATING,
	NON_EATING
} t_status;

typedef enum e_side{
	RIGHT = 0,
	LEFT
}	t_side;

typedef struct s_fork {
	pthread_mutex_t	*lock;
	t_bool			is_holdable;
} 	t_fork;

typedef struct s_arg {
	int			n_philos;
	time_t		time_die;
	time_t		time_eat;
	time_t		time_jam;
	int			required_meal;
}	t_arg;

typedef struct s_philo {
	pthread_t		*tid; /// address
	int 			id;
	int				eat_cnt;
	time_t			time_created;
	t_fork			forks[2]; /// address
	t_arg			arg;
};

#define NUM_LOCKS 4

typedef struct s_lock {
	pthread_mutex_t read_lock;
	pthread_mutex_t write_lock;
}	t_lock;


typedef struct s_rsc {
	t_fork		*forks;
	pthread_t	*philos;
}	t_rsc;


/// @file utils, libft.c
int		ft_atoi(const char *str);
void	*ft_memalloc(size_t size);
int		ft_isdigit(const char c);
int		ft_isspace(const char c);
int		ft_all_satisfy(int (*f)(char c), char *s);

/// @file utils, utils.c
pthread_mutex_t	*init_mutexes(int count);
time_t			ft_gettime(void);
void			ft_usleep(time_t time);

/// @file utils, error.c
int	ft_error_msg(const char *msg);
#endif