/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 11:35:01 by daflynn           #+#    #+#             */
/*   Updated: 2026/02/28 11:35:03 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
#include <math.h>

#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

int	handle_keypress(int keycode, t_game *game)
{
	double	new_x;
	double	new_y;
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == 65307) // ESC
		exit(0);

	if (keycode == 'w')
	{
		new_x = game->pos_x + game->dir_x * MOVE_SPEED;
		new_y = game->pos_y + game->dir_y * MOVE_SPEED;
		if (game->world_map[(int)new_x][(int)new_y] == 0)
		{
			game->pos_x = new_x;
			game->pos_y = new_y;
		}
	}
	if (keycode == 's')
	{
		new_x = game->pos_x - game->dir_x * MOVE_SPEED;
		new_y = game->pos_y - game->dir_y * MOVE_SPEED;
		if (game->world_map[(int)new_x][(int)new_y] == 0)
		{
			game->pos_x = new_x;
			game->pos_y = new_y;
		}
	}
	if (keycode == 'a')
	{
		old_dir_x = game->dir_x;
		game->dir_x = game->dir_x * cos(ROT_SPEED) - game->dir_y * sin(ROT_SPEED);
		game->dir_y = old_dir_x * sin(ROT_SPEED) + game->dir_y * cos(ROT_SPEED);
		old_plane_x = game->plane_x;
		game->plane_x = game->plane_x * cos(ROT_SPEED) - game->plane_y * sin(ROT_SPEED);
		game->plane_y = old_plane_x * sin(ROT_SPEED) + game->plane_y * cos(ROT_SPEED);
	}
	if (keycode == 'd')
	{
		old_dir_x = game->dir_x;
		game->dir_x = game->dir_x * cos(-ROT_SPEED) - game->dir_y * sin(-ROT_SPEED);
		game->dir_y = old_dir_x * sin(-ROT_SPEED) + game->dir_y * cos(-ROT_SPEED);
		old_plane_x = game->plane_x;
		game->plane_x = game->plane_x * cos(-ROT_SPEED) - game->plane_y * sin(-ROT_SPEED);
		game->plane_y = old_plane_x * sin(-ROT_SPEED) + game->plane_y * cos(-ROT_SPEED);
	}

	render_frame(game);
	return (0);
}

int	handle_close(t_game *game)
{
	(void)game;
	exit(0);
}
