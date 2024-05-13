/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:36:22 by minakim           #+#    #+#             */
/*   Updated: 2024/05/13 17:43:42 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_rand(void)
{
	static unsigned long int	random_number;
	char						*base;
	unsigned long int			seed;

	base = malloc(1);
	if (!base)
		ft_error_general("Failed to generate random number\n");
	seed = (unsigned long int)base;
	free(base);
	random_number = random_number * seed * 1103515245 + 12345;
	return ((unsigned int)(random_number / 65536) % 17);
}

int	ft_readline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
	return (i);
}

void	ft_mlx_image_to_window(t_game *game, mlx_image_t *mlx_image, \
			int x, int y)
{
	mlx_image_to_window(game->mlx, mlx_image, x * IMG_WIDTH, y * IMG_HEIGHT);
	if (!mlx_image)
	{
		ft_free_map_repo(game->map.repo);
		ft_error_general("mlx image uninit");
	}
}
#include <stdlib.h>
void	place_png_to_img(t_game *game, mlx_image_t **img, char *path)
{
	mlx_texture_t	*my_texture;

	my_texture = mlx_load_png(path);
	ft_printf("path: %s\n", path);
	system("pwd");
	
	if (!my_texture)
		ft_error_and_free_map("failed to read png file."
							  "can not open image.", game);
	*img = mlx_texture_to_image(game->mlx, my_texture);
	mlx_delete_texture(my_texture);
	if (!*img)
		ft_error_and_free_map("there is no image."
							  "can not open image.", game);
}

int	ft_get_len(long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}
