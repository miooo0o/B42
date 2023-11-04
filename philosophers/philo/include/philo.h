/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:52:27 by minakim           #+#    #+#             */
/*   Updated: 2023/11/04 18:56:43 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_locktype{
	LOCK_PRINT = 0,
	LOCK_SCHEDULE,
}	t_locktype;

typedef enum e_status{
	NONE = 0,
	ALIVE,
	DEAD
} t_status;

/// struct
typedef struct s_owned {
	int 			id;
	int 			n_ate;
	long long		t_creation;
	long long		t_last_meal;
	int				status;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_owned;

typedef struct s_handler {
	int				n_philos;
	long long		time_die;
	long long		time_eat;
	long long		time_jam;
	int				required_eat;
	int				*next;
	int				*time_table;
}	t_handler;

typedef struct s_philo {
	pthread_t	*thread;
	t_owned		owned;
} t_philo;

typedef struct s_resource
{
	pthread_mutex_t	**forks;
	pthread_mutex_t	*lock_print;
	pthread_mutex_t *lock_schedule;
}					t_resource;

int	ft_atoi(const char *str);
int	ft_error(char *s);
int	ft_isdigit(const char c);
int	ft_isspace(const char c);
int ft_all_satisfy(int (*f)(char c), char *s);


int	valid_args(int ac, char **av);

#endif