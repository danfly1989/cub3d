/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 00:00:00 by daflynn           #+#    #+#             */
/*   Updated: 2026/02/28 15:51:31 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(t_game *game)
{
	int	i;

	if (!game->map)
		return ;
	i = 0;
	while (i < game->map_height)
		free(game->map[i++]);
	free(game->map);
	game->map = NULL;
}

static void	free_tex_paths(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex_path[i])
			free(game->tex_path[i]);
		game->tex_path[i] = NULL;
		i++;
	}
}

static void	destroy_mlx_images(t_game *game)
{
	int	i;

	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	i = 0;
	while (i < 4)
	{
		if (game->texture[i].img)
			mlx_destroy_image(game->mlx, game->texture[i].img);
		i++;
	}
}

void	cleanup(t_game *game)
{
	free_map(game);
	free_tex_paths(game);
	if (!game->mlx)
		return ;
	destroy_mlx_images(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}
