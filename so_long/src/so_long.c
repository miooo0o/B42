/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi■■■■■ <mi■■■■■@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:45:22 by mi■■■■■           #+#    #+#             */
/*   Updated: 2023/04/23 18:33:27 by mi■■■■■          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	place_texture(t_game *game)
{
	place_floor_with_texture(game);
	place_layer_with_texture(game);
	ft_printf("--- Get ready to play! ---\n");
}

void	clean_up(t_game *game)
{
	delete_all_image(game);
	ft_free_map_repo(game->map.repo);
	mlx_terminate(game->mlx);
	ft_printf("--- clean up all data . . .\n");
}

int	main(int ac, char **av)
{
	t_game	game;

	check_argument(ac, av, &game);
	init_value(&game);
	game.fd = open(av[1], O_RDONLY);
	if (game.fd < 0 || game.fd == 0)
		ft_error_general("Failed to open file. [fd]");
	init_map(av, &game);
	valid_map(&game);
	init_mlx(&game);
	init_floor(&game);
	place_texture(&game);
	mlx_key_hook(game.mlx, &key_hook, &game.mlx);
	mlx_loop(game.mlx);
	clean_up(&game);
}
