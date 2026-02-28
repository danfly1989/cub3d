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

/*
** Zero-initialise game struct and set sentinel values for the fields
** that the parser fills in. -1 is used for colors so is_meta_complete()
** can distinguish "not yet set" from a valid packed RGB of 0.
*/
void	init_game(t_game *game)
{
	int	i;

	ft_bzero(game, sizeof(t_game));
	game->screen_width = 1280;
	game->screen_height = 720;
	game->floor_color = -1;
	game->ceil_color = -1;
	i = 0;
	while (i < 4)
		game->tex_path[i++] = NULL;
}

/*
** Initialise the MLX window and image buffer.
** Called after the parser has filled in game->screen_width/height.
*/
static void	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		parse_error("mlx_init failed");
	game->win = mlx_new_window(game->mlx,
			game->screen_width, game->screen_height, "Cub3D");
	if (!game->win)
		parse_error("mlx_new_window failed");
	game->img.img = mlx_new_image(game->mlx,
			game->screen_width, game->screen_height);
	if (!game->img.img)
		parse_error("mlx_new_image failed");
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./cub3D <map.cub>\n", 2);
		return (1);
	}
	init_game(&game);
	parse_cub_file(&game, argv[1]);
	init_window(&game);
	load_textures(&game);
	render_frame(&game);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, handle_close, &game);
	mlx_loop(game.mlx);
	return (0);
}
