#include "philo.h"

int check_args(int max, char **argv, int val[5])
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (++i < max)
	{
		if (!ft_all_satisfy(ft_isdigit, argv[i]))
			return (ft_error_msg("input should be digit only"), 0);
		val[j] = ft_atoi(argv[i]);
		if (val[j] == -1)
			return (ft_error_msg("too large value"), 0);
		j++;
	}
	return (1);
}

int valid_args(int argc, char **argv)
{
	t_rsc	*rsc;
	int		val[5];

	if (argc < 5 || argc > 6)
		return (0);
	rsc = rsc_instance();
	if (!check_args(argc, argv, val))
		return (0);
	rsc->n_philos = val[0];
	rsc->time_die = val[1];
	rsc->time_eat = val[2];
	rsc->time_jam = val[3];
	rsc->required_meal = SET_NONE;
	if (argc == 6)
		rsc->required_meal = val[4];
	return (1);
}