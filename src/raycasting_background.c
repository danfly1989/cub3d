/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_background.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:10:00 by daflynn           #+#    #+#             */
/*   Updated: 2026/02/28 16:10:00 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->img.addr + (y * game->img.line_length
			+ x * (game->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*
** Fill ceiling (top half) with game->ceil_color
** and floor (bottom half) with game->floor_color.
** Both values are parsed from the .cub file as 0x00RRGGBB.
*/
void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			if (y < game->screen_height / 2)
				put_pixel(game, x, y, game->ceil_color);
			else
				put_pixel(game, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}
