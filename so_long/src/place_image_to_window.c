/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_image_to_window.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi■■■■■ <mi■■■■■@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 23:00:45 by mi■■■■■           #+#    #+#             */
/*   Updated: 2023/04/23 16:56:04 by mi■■■■■          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	place_floor_with_texture(t_game *game)
{
	int							y;
	int							x;
	static unsigned long int	random_number;

	random_number = 1;
	y = -1;
	while (++y < game->map.columns)
	{
		x = -1;
		while (++x < game->map.rows)
		{
			random_number = ft_rand();
			random_map_generate(game, &random_number, x, y);
		}
	}
	ft_printf("--- floor set . . .\n");
}

void	place_layer_with_texture(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < game->map.columns)
	{
		x = -1;
		while (++x < game->map.rows)
		{
			if (game->map.repo[y][x] == CHAR_WALL)
				mlx_image_to_window(game->mlx, game->img.wall, \
					x * IMG_WIDTH, y * IMG_HEIGHT);
			else if (game->map.repo[y][x] == CHAR_PLAYER)
				init_player(game, x, y);
			else if (game->map.repo[y][x] == CHAR_COLLLECT)
				init_collect(game, x, y, &game->count);
			else if (game->map.repo[y][x] == CHAR_EXIT)
				init_exit(game, x, y);
		}
	}
	ft_mlx_image_to_window(game, game->img.number[0], 1, game->map.columns - 1);
	ft_printf("--- layer set . . .\n");
	game->count = 0;
}
