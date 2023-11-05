/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:52:27 by minakim           #+#    #+#             */
/*   Updated: 2023/11/05 23:34:23 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define LOCKTYPE_COUNT 7

typedef enum e_locktype{
	LOCK_PRINT = 0,
	LOCK_STATUS,
	LOCK_START,
	LOCK_FORK,
	LOCK_EAT,
	LOCK_TIME,
	LOCK_DEATH
}	t_locktype;

typedef enum e_status{
	NONE = 0,
	ALIVE,
	DEAD
} t_status;

typedef enum e_numbertype
{
	NUM_NONE = 0,
	NUM_ODD,
	NUM_EVEN
}	t_numbertype;

# define ERRORTYPE_COUNT 6

typedef enum e_errortype
{
	MALLOC = 0,
	THREAD_INIT,
	THREAD_CREATE,
	PHILO_INIT,
	MUTEX_LOCK,
	MUTEX_UNLOCK
}	t_errortype;


/// struct
typedef struct s_config {
	int				n_philos;
	long long		time_die;
	long long		time_eat;
	long long		time_jam;
	int				required_eat;
	int				death_occurs;
	pthread_mutex_t	**forks;
	pthread_mutex_t	**locks;
	pthread_mutex_t *start_flag;
}	t_config;

typedef struct s_philo {
	pthread_t		*thread;
	int 			id;
	int 			num_type;
	int 			n_ate;
	long long		t_creation;
	long long		t_last_meal;
	int				status;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t *start_flag;
} t_philo;


t_config	*conf_instance(void);


int		ft_atoi(const char *str);
void	*ft_memalloc(size_t size);
int		ft_isdigit(const char c);
int		ft_isspace(const char c);
int		ft_all_satisfy(int (*f)(char c), char *s);
int		ft_iseven(int number);

t_config	*config_from_args(int ac, char **av);
t_philo	**init_philos(t_config *conf);

time_t	ft_get_time(void);
int		ft_usleep(time_t time);

void	ft_error_msg(const char *msg);
void	ft_error_type(t_errortype type);
int		check(int result, t_errortype type);

void	*ft_free_till_index(void **target, int index);
void	ft_free_2d(void **target);
void	ft_free(void *target);

int eating(t_config *conf, t_philo *philo);

int philosophers(t_config	*conf, t_philo **philos);
#endif