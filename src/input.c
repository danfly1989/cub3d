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

#define MOVE_SPEED 0.05
#define ROT_SPEED  0.03
#define ESC_KEY    65307
#define LEFT_KEY   65361
#define RIGHT_KEY  65363

static void	move_player(t_game *game, double direction)
{
	double	new_x;
	double	new_y;

	new_x = game->pos_x + (game->dir_x * MOVE_SPEED * direction);
	new_y = game->pos_y + (game->dir_y * MOVE_SPEED * direction);
	if (!is_wall(game, (int)new_x, (int)game->pos_y))
		game->pos_x = new_x;
	if (!is_wall(game, (int)game->pos_x, (int)new_y))
		game->pos_y = new_y;
}

static void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dir_x;
	game->dir_x = (game->dir_x * cos(angle)) - (game->dir_y * sin(angle));
	game->dir_y = (old_dir_x * sin(angle)) + (game->dir_y * cos(angle));
	old_plane_x = game->plane_x;
	game->plane_x = (game->plane_x * cos(angle))
		- (game->plane_y * sin(angle));
	game->plane_y = (old_plane_x * sin(angle))
		+ (game->plane_y * cos(angle));
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
	{
		cleanup(game);
		exit(0);
	}
	if (keycode == 'w')
		move_player(game, 1.0);
	if (keycode == 's')
		move_player(game, -1.0);
	if (keycode == LEFT_KEY || keycode == 'a')
		rotate_player(game, -ROT_SPEED);
	if (keycode == RIGHT_KEY || keycode == 'd')
		rotate_player(game, ROT_SPEED);
	render_frame(game);
	return (0);
}

int	handle_close(t_game *game)
{
	cleanup(game);
	exit(0);
	return (0);
}
