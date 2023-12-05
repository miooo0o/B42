/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:24:22 by minakim           #+#    #+#             */
/*   Updated: 2023/12/05 17:01:23 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>

/// @note Define in short words
typedef long long		t_ll;
typedef unsigned int	t_ui;
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_pth;
typedef struct s_data	t_data;

/// @brief basic
# define ALIGN 0
# define MAX_PHILOS 200
# define INTERVAL 100
# define WAIT_TURN 100
# define NONE -1

/// @brief error msg
# define EINVAL "Invalid argument, Numeric/non-negative numbers only."
# define EINARGNUM "Invalid number of arguments"
# define ENOMEM "Cannot allocate memory"
# define ETHREADCREATE \
"Failed to create thread: Insufficient resources or invalid attributes"

/// @enum bool, logs
typedef enum e_bool{
	FALSE,
	TRUE
}	t_bool;

/// @note Used to specify the state when the philosopher's status log is output.
typedef enum e_logs {
	EAT,
	SLEEP,
	THINK,
	DIE,
	FORK,
	DONE
} t_logs;

typedef enum e_state {
	THINKING,
	EATING,
	NORMAL_HUNGRY,
	SEVERELY_HUNGRY
} t_state;

typedef struct e_fork {
	t_bool 	is_taken;
	t_mutex	*mx;
}	t_fork;

/// @note mx: mutex, m: malloc
typedef struct s_philo {
	int 	id;
	t_pth	pth;
	t_pth	mon_pth;
	t_fork	r_fork;
	t_fork	l_fork;
	t_mutex	mx_meal;	/// mutex

//	/// TODO: 아직 구현하지 않음
//	t_state	state;		/// opt
//	t_mutex	mx_state;	/// opt mutex
//	///

	t_ll	creation_us;
	t_ll	last_meal_us;
	int		left_meal;
	t_bool	is_fulled;
	t_bool	death_occurs;

	t_data	*data;		/// address

	int		n_philos;
	t_ll	die_us;
	t_ll	eat_us;
	t_ll	jam_us;
} 	t_philo;

/// @note time_x : saved as micro second
typedef struct s_data {
	int		n_philos;
	t_ll	die_us;
	t_ll	eat_us;
	t_ll	jam_us;
	int		required_meals;
	t_mutex	mx_death;
	t_mutex	mx_log;
	t_philo	*arr_m_philos;	/// threads
	t_mutex *arr_m_forks;	/// mutexs
}	t_data;

/// @note all files in src
/// @file philosophers.c
int		philosophers(t_data *data);

/// @file init.c
int		check_args(int ac, char **av);
t_bool	init_data(int ac, char **av, t_data *data);

///	@file lifecycle.c, eat.c
void	eat(t_philo *philo);
void	*ft_lifecycle(void *ptr);

/// @file monitor.c
void	*ft_monitor(void *ptr);

/// @note all files in src/utils
/// @file utils, libft.c
int		ft_atoi(const char *str);
int		ft_isdigit(char c);
int		ft_isspace(char c);
int		ft_strlen(const char *str);

/// @file utils, libft_extend.c
void	*ft_memalloc(size_t size);
int		ft_all_satisfy(int (*f)(char c), char *s);

/// @file utils, utils.c
void	ft_perror(const char *msg);
t_ll	ft_gettime_us(void);
void	ft_usleep_us(t_ll duration_usec);
void	print_log(t_philo *philo, t_logs type);

#endif