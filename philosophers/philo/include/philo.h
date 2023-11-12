/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:24:22 by minakim           #+#    #+#             */
/*   Updated: 2023/11/12 20:45:38 by minakim          ###   ########.fr       */
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
	NONE_SET = -1,
	FALSE,
	TRUE
}	t_bool;

typedef enum e_steps {
	EAT,
	SLEEP,
	THINK,
	DIE,
	FORK
} t_steps;

typedef enum e_side {
	RIGHT = 0,
	LEFT
}	t_side;

typedef enum e_res{
	SUCCESS,
	MEM_ERROR,
	INIT_ERROR,
	INPUT_VALID_ERROR,
}	t_res;

typedef struct s_arg {
	int			n_philos;
	long long	time_die;
	long long	time_eat;
	long long	time_jam;
	long long	creation_time;
	int			required_n_meals;
}	t_arg;

typedef struct s_philo {
	int 		id;
	t_arg		*args;
	t_steps		step;
	t_bool		is_alive;
	int			eat_cnt;
	long long	last_meal;
} t_philo;

typedef struct s_mutex {
	pthread_mutex_t	;
};

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

int		writer(long *dest, const long *src);
long	reader(const long *target);

/// @file utils, error.c
int	ft_error_msg(const char *msg);
#endif