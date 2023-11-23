/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:24:22 by minakim           #+#    #+#             */
/*   Updated: 2023/11/21 19:30:03 by minakim          ###   ########.fr       */
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

# define ALIGN 0
# define NONE -1
# define CHECK_INTERVAL 1

typedef enum e_bool{
	FALSE = 0,
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
typedef struct s_rsc	t_rsc;

/// @note time_x : milli second
typedef struct s_data {
	int		n_philos;
	int		last_philo_id;
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
	t_mutex	*r_fork;	/// address
	t_mutex	*l_fork;	/// address
} 	t_philo;

typedef struct s_rsc {
	t_mutex	*arr_m_forks;
	t_mutex	*arr_m_n_eaten;
	t_mutex *arr_m_status; /// change "is_alive"
	t_mutex *arr_m_last_meal;
	t_mutex	print;
	t_mutex	timetable; /// "change "who_next"
	t_philo	*arr_m_philos;
	t_data	*data;
	int 	*arr_m_timetable;
	int		*who_next;
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
t_ll	to_microsec(t_ll millisec);
t_ll	to_millisec(t_ll microsec);


void	*death_is_sure_to_all(void	*p);
void	*lifecycle(void *p);

/// @file utils, error.c
int	ft_error_msg(const char *msg);

t_exit	check_args(int argc, char **argv);

t_exit	init(void);

t_data	*data_instance(void);
t_rsc	*rsc_instance(void);

void	ft_print(t_philo *philo, t_steps step);
t_bool	all_alive(t_philo *philo);
t_exit	destroy_arr_m_mutex(int count, t_mutex *target);
t_exit	free_and_destroy(void);
#endif