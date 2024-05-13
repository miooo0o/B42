/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi■■■■■ <mi■■■■■@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:54:26 by mi■■■■■           #+#    #+#             */
/*   Updated: 2023/04/22 19:54:27 by mi■■■■■          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_floor(t_game *game)
{
	place_png_to_img(game, &game->img.floor[0], PNG_FLOOR0);
	place_png_to_img(game, &game->img.floor[1], PNG_FLOOR1);
	place_png_to_img(game, &game->img.floor[2], PNG_FLOOR2);
	place_png_to_img(game, &game->img.floor[3], PNG_FLOOR3);
	place_png_to_img(game, &game->img.floor[4], PNG_FLOOR4);
	place_png_to_img(game, &game->img.floor[5], PNG_FLOOR5);
	place_png_to_img(game, &game->img.floor[6], PNG_FLOOR6);
	place_png_to_img(game, &game->img.floor[7], PNG_FLOOR7);
	place_png_to_img(game, &game->img.floor[8], PNG_FLOOR8);
	place_png_to_img(game, &game->img.floor[9], PNG_FLOOR9);
	place_png_to_img(game, &game->img.wall, PNG_WALL);
	place_png_to_img(game, &game->img.number[0], PNG_NUM0);
}

void	init_player(t_game *game, int x, int y)
{
	place_png_to_img(game, &game->img.player.front[0].image, PNG_PLAYER_FRONT0);
	set_player_position(&game->img.player.front[0], &game->position);
	mlx_image_to_window(game->mlx, game->img.player.front[0].image, \
		x * IMG_WIDTH, y * IMG_HEIGHT);
}

void	init_collect(t_game *game, int x, int y, int *count)
{
	place_png_to_img(game, &game->img.collect[*count].image, PNG_COLLECT);
	game->img.collect[*count].x = x;
	game->img.collect[*count].y = y;
	mlx_image_to_window(game->mlx, game->img.collect[*count].image, \
		x * IMG_WIDTH, y * IMG_HEIGHT);
	(*count)++;
}

void	init_exit(t_game *game, int x, int y)
{
	place_png_to_img(game, &game->img.exits[0].image, PNG_EXIT_CLOSE);
	game->img.exits[0].x = x;
	game->img.exits[0].y = y;
	place_png_to_img(game, &game->img.exits[1].image, PNG_EXIT_OPEN);
	game->img.exits[1].x = x;
	game->img.exits[1].y = y;
	mlx_image_to_window(game->mlx, game->img.exits[0].image, \
		x * IMG_WIDTH, y * IMG_HEIGHT);
}

void	random_map_generate(t_game *game, unsigned long int *random_number, \
	int x, int y)
{
	if (*random_number == 0 || *random_number >= 10)
		ft_mlx_image_to_window(game, game->img.floor[0], x, y);
	else if (*random_number == 1)
		ft_mlx_image_to_window(game, game->img.floor[1], x, y);
	else if (*random_number == 2)
		ft_mlx_image_to_window(game, game->img.floor[2], x, y);
	else if (*random_number == 3)
		ft_mlx_image_to_window(game, game->img.floor[3], x, y);
	else if (*random_number == 4)
		ft_mlx_image_to_window(game, game->img.floor[4], x, y);
	else if (*random_number == 5)
		ft_mlx_image_to_window(game, game->img.floor[5], x, y);
	else if (*random_number == 6)
		ft_mlx_image_to_window(game, game->img.floor[6], x, y);
	else if (*random_number == 7)
		ft_mlx_image_to_window(game, game->img.floor[7], x, y);
	else if (*random_number == 8)
		ft_mlx_image_to_window(game, game->img.floor[8], x, y);
	else if (*random_number == 9)
		ft_mlx_image_to_window(game, game->img.floor[9], x, y);
}
