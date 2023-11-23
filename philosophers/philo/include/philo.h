/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:24:22 by minakim           #+#    #+#             */
/*   Updated: 2023/11/23 18:31:44 by minakim          ###   ########.fr       */
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

typedef enum e_exit{
	SUCCESS,
	MEM_ERR,
	INIT_ERR,
	INPUT_VALID_ERR,
}	t_exit;

typedef struct s_fork
{
	t_bool	is_occupied;
	t_mutex	mutex;
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
	t_ll	time_die;
	t_ll	time_eat;
	t_ll	time_jam;
	int		required_n_meals;
	t_bool	is_n_eaten_finished;
	t_bool	all_alive;
	t_mutex	mt_dead;
	t_mutex	mt_death_time;
	t_mutex	mt_meal;
	t_mutex	mt_print;
	t_mutex	mt_time;
	t_philo	**arr_m_philos;
	t_fork	**arr_m_forks;
}	t_data;

/// @file utils, libft.c
int		ft_atoi(const char *str);
void	*ft_memalloc(size_t size);
int		ft_isdigit(const char c);
int		ft_isspace(const char c);
int		ft_all_satisfy(int (*f)(char c), char *s);

/// @file
int	ft_error_msg(const char *where, t_exit err);

/// @file utils, utils.c
t_exit	init_arr_m_mutex(int count, t_mutex **target);
t_exit	destroy_arr_m_mutex(int count, t_mutex *target);

#endif