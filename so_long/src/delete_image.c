/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:37:18 by minakim           #+#    #+#             */
/*   Updated: 2024/05/13 17:37:18 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi■■■■■ <mi■■■■■@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:56:45 by mi■■■■■           #+#    #+#             */
/*   Updated: 2023/04/23 19:49:01 by mi■■■■■          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	delete_item(t_game *game, int x, int y)
{
	int	i;
	int	collect_x;
	int	collect_y;

	collect_x = 0;
	collect_y = 0;
	game->map.repo[y][x] = '0';
	i = -1;
	while (++i < game->map.collects && game->count < game->map.collects)
	{
		if (game->count >= game->map.collects)
			break ;
		collect_x = game->img.collect[i].x;
		collect_y = game->img.collect[i].y;
		if (collect_x == x && collect_y == y)
		{
			mlx_delete_image(game->mlx, game->img.collect[i].image);
			game->count++;
		}
	}
}

void	delete_collectible(t_game *game)
{
	int	finded;
	int	y;
	int	x;

	y = -1;
	x = -1;
	ft_printf("cols[%d], rows[%d]\n", game->map.columns, game->map.rows);
	while (++y < game->map.columns)
	{
		x = -1;
		while (++x < game->map.rows)
		{
			if (game->map.repo[y][x] == CHAR_COLLLECT)
				delete_item(game, x, y);
		}
	}
	if (game->count != game->map.collects)
		ft_error_and_free_map("could not delete all floor image", game);
	ft_printf("--- all collectible items deleted . . .\n");
}

void	delete_player(t_game *game)
{
	int	i;

	i = -1;
	if (!game->img.player.front[++i].image)
		return ;
	mlx_delete_image(game->mlx, game->img.player.front[0].image);
}

void	delete_floor(t_game *game)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		mlx_delete_image(game->mlx, game->img.floor[i]);
		i++;
	}
}

void	delete_all_image(t_game *game)
{
	delete_collectible(game);
	delete_floor(game);
	delete_player(game);
	delete_num(game);
	mlx_delete_image(game->mlx, game->img.exits[0].image);
	mlx_delete_image(game->mlx, game->img.exits[1].image);
	mlx_delete_image(game->mlx, game->img.wall);
}

/* // only with map/small.map 
void	test_all_delete(t_game *game)
{
	mlx_delete_image(game->mlx, game->img.exits[0].image);
	mlx_delete_image(game->mlx, game->img.exits[1].image);
	mlx_delete_image(game->mlx, game->img.wall);
	mlx_delete_image(game->mlx, game->img.floor[0]);
	mlx_delete_image(game->mlx, game->img.floor[1]);
	mlx_delete_image(game->mlx, game->img.floor[2]);
	mlx_delete_image(game->mlx, game->img.floor[3]);
	mlx_delete_image(game->mlx, game->img.floor[4]);
	mlx_delete_image(game->mlx, game->img.floor[5]);
	mlx_delete_image(game->mlx, game->img.floor[6]);
	mlx_delete_image(game->mlx, game->img.floor[7]);
	mlx_delete_image(game->mlx, game->img.floor[8]);
	mlx_delete_image(game->mlx, game->img.floor[9]);
	mlx_delete_image(game->mlx, game->img.collect[0].image);
	mlx_delete_image(game->mlx, game->img.collect[1].image);
	mlx_delete_image(game->mlx, game->img.player.front[0].image);
	ft_free_map_repo(game->map.repo);
	mlx_terminate(game->mlx);
}
*/