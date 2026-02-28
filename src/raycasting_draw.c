/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:00:00 by daflynn           #+#    #+#             */
/*   Updated: 2026/02/28 16:00:00 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_column
{
	t_img	*tex;
	double	step;
	double	tex_pos;
	int		x;
}t_column;

static void	draw_wall_pixel(t_game *game, t_ray *ray, t_column *col, int y)
{
	int				tex_y;
	unsigned int	color;
	char			*dst;

	tex_y = (int)col->tex_pos;
	if (tex_y >= col->tex->height)
		tex_y = col->tex->height - 1;
	color = get_tex_pixel(col->tex, ray->tex_x, tex_y);
	if (ray->side == 1)
		color = (color >> 1) & 0x7F7F7F;
	dst = game->img.addr + (y * game->img.line_length
			+ col->x * (game->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_wall_column(t_game *game, t_ray *ray, int x)
{
	t_column	col;
	int			y;

	col.tex = &game->texture[get_texture_index(ray)];
	calculate_texture_coords(game, ray, col.tex);
	col.step = 1.0 * col.tex->height / ray->line_height;
	col.tex_pos = (ray->draw_start - game->screen_height / 2
			+ ray->line_height / 2) * col.step;
	col.x = x;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		draw_wall_pixel(game, ray, &col, y);
		col.tex_pos += col.step;
		y++;
	}
}
