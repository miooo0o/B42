/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:24:22 by minakim           #+#    #+#             */
/*   Updated: 2023/11/28 16:34:52 by minakim          ###   ########.fr       */
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
# define MAX_PHILOS 200

# define MEM_ERROR_MSG "mem fail."
# define INIT_ERROR_MSG "init fail."
# define INPUT_VALID_ERROR_MSG "input valid fail."

typedef long long		t_ll;
typedef unsigned int	t_ui;
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_pth;
typedef struct s_data	t_data;

typedef enum e_bool{
	FALSE = 0,
	TRUE
}	t_bool;

typedef enum e_logs {
	EAT,
	SLEEP,
	THINK,
	DIE,
	FORK
} t_logs;

typedef enum e_side {
	RIGHT = 0,
	LEFT
}	t_side;

typedef enum e_sec{
	GET_MS = 0,
	GET_USEC
}	t_sec;
typedef enum e_exit{
	SUCCESS,
	MEM_ERR,
	INIT_M_ERR,
	INPUT_VALID_ERR,
	GETTIME_ERR
}	t_exit;

typedef struct s_fork
{
	t_bool	is_occupied;
	t_mutex	m;
}	t_fork;

typedef struct s_philo {
	int 	id;
	t_pth	*thread;
	t_bool	is_alone;
	t_ll	creation_time;
	t_ll	current;
	int		n_eaten;
	t_bool	is_alive;
	t_ll	last_meal;
	t_fork	*r_fork;	/// address
	t_fork	*l_fork;	/// address
	t_data	*data;		/// address
} 	t_philo;

/// @note time_x : saved as micro second
typedef struct s_data {
	int		n_philos;
	int		last_philo_id;
	t_ll	time_die_usec;
	t_ll	time_eat_usec;
	t_ll	time_jam_usec;
	int		required_n_meals;
	t_bool	is_n_meals_finished;
	t_bool	all_alive;
	t_mutex	m_dead;
	t_mutex	m_death_time;
	t_mutex	m_meal;
	t_mutex	m_print;
	t_mutex	m_time;
	t_philo	**arr_m_philos;	/// address, threads
	t_fork	**arr_m_forks;	/// address, mutexs
}	t_data;

/// @file utils, libft.c
int		ft_atoi(const char *str);
void	*ft_memalloc(size_t size);
int		ft_isdigit(char c);
int		ft_isspace(char c);
int		ft_all_satisfy(int (*f)(char c), char *s);

/// @file
int	ft_err(const char *f_name, t_exit err);

/// @file utils, utils.c

t_exit	init_arr_m_mutex(int count, t_mutex **target);
t_exit	destroy_arr_m_mutex(int count, t_mutex *target);

t_exit	check_args(int argc, char **argv);
t_data	*init_data(int argc, char **argv);

/// @file utils_time.c
t_ll	ft_gettime(t_philo *philo, t_sec mode);
t_ll	current_time_ms(void);
t_ll	current_time_usec(void);
t_ll	ms_to_usec(t_ll	milli);
t_ll	usec_to_ms(t_ll micro);

#endif