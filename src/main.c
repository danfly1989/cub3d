/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 10:43:15 by daflynn           #+#    #+#             */
/*   Updated: 2026/02/28 11:36:10 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	game->screen_width = 200;
	game->screen_height = 100;

	game->pos_x = 12.0;
	game->pos_y = 12.0;
	game->dir_x = -1.0;
	game->dir_y = 0.0;
	game->plane_x = 0.0;
	game->plane_y = 0.66;

	game->mlx = mlx_init();
	if (!game->mlx)
		exit(1);

	game->win = mlx_new_window(game->mlx,
			game->screen_width,
			game->screen_height,
			"Cub3D Test Wall");
	if (!game->win)
		exit(1);

	game->img.img = mlx_new_image(game->mlx,
			game->screen_width,
			game->screen_height);
	if (!game->img.img)
		exit(1);

	game->img.addr = mlx_get_data_addr(
			game->img.img,
			&game->img.bits_per_pixel,
			&game->img.line_length,
			&game->img.endian);
}

void	init_world_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 24)
	{
		j = 0;
		while (j < 24)
		{
			game->world_map[i][j] = 0;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < 24)
	{
		game->world_map[10][i] = 1;
		i++;
	}
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	init_world_map(&game);
	render_frame(&game);
	mlx_hook(game.win, 2, 1L<<0, handle_keypress, &game);
mlx_hook(game.win, 17, 0, handle_close, &game);
	mlx_loop(game.mlx);
	return (0);
}
