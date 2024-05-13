/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi■■■■■ <mi■■■■■@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:52:03 by mi■■■■■           #+#    #+#             */
/*   Updated: 2023/04/23 18:27:05 by mi■■■■■          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_2d_malloc(t_game *game)
{
	if (!game->map.repo)
	{
		game->map.repo = (char **)malloc(sizeof(char *) * 270);
		if (!game->map.repo)
			ft_error_general("Failed to allocate memory for map.");
		ft_memset(game->map.repo, 0, 270);
	}
	ft_printf("--- reading map . . . .\n");
}

void	check_map_len(t_game *game, char *line, int index)
{
	int	len;

	len = ft_readline(line);
	if (index == 0)
		game->map.rows = len;
	return ;
}

void	is_emtpy_file(char *line)
{
	int	len;

	if (line == NULL)
		ft_error_general("Map file is empty.");
	len = ft_readline(line);
}

void	init_map(char **av, t_game *game)
{
	char	*line;
	int		i;

	line = get_next_line(game->fd);
	is_emtpy_file(line);
	i = 0;
	while (line && !(line[0] == '\n'))
	{
		if (i >= 270)
			ft_error_and_free_map("Map file too large.", game);
		if (game->map.repo == NULL)
			map_2d_malloc(game);
		game->map.repo[i] = malloc(sizeof(char) * (ft_readline(line) + 1));
		if (!game->map.repo[i])
			ft_error_and_free_map("Failed to allocate memory for a \
line in the map.", game);
		check_map_len(game, line, i);
		ft_strlcpy(game->map.repo[i], line, game->map.rows + 1);
		i++;
		free(line);
		line = get_next_line(game->fd);
	}
	game->map.columns = i;
	free(line);
	close(game->fd);
}
