/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:24:22 by minakim           #+#    #+#             */
/*   Updated: 2023/11/13 15:47:47 by minakim          ###   ########.fr       */
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
}	t_exit;

typedef long long		t_ll;
typedef unsigned int	t_ui;
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_pth;
typedef struct s_data	t_data;

typedef struct s_data {
	int		n_philos;
	t_ll	time_die;
	t_ll	time_eat;
	t_ll	time_jam;
	int		required_n_meals;
}	t_data;

typedef struct s_philo {
	int 	id;
	t_ll	creation_time;
	int		n_eaten;
	t_bool	is_alive;
	t_ll	last_meal;
	t_steps	step;
	t_mutex	*lock; /// address
	t_mutex	*r_fork; /// address
	t_mutex	*l_fork; /// address
} 	t_philo;


typedef struct s_rsc {
	t_mutex	*arr_m_fork;
	t_mutex	*arr_m_lock;
	t_philo	*arr_m_philos;
	t_mutex	print;
	t_mutex	death;
} t_rsc;

/// @file utils, libft.c
int		ft_atoi(const char *str);
void	*ft_memalloc(size_t size);
int		ft_isdigit(const char c);
int		ft_isspace(const char c);
int		ft_all_satisfy(int (*f)(char c), char *s);

/// @file utils, utils.c
t_exit	init_arr_m_mutex(int count, t_mutex **target);
time_t	ft_gettime(void);
void	ft_usleep(time_t time);

/// @file utils, error.c
int	ft_error_msg(const char *msg);

t_exit	check_args(int argc, char **argv);
void	init_data(int argc, char **argv);

t_exit	init(int argc, char **argv);

t_data	*data_instance(void);
t_rsc	*rsc_instance(void);
#endif