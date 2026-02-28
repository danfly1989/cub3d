/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:32:52 by daflynn           #+#    #+#             */
/*   Updated: 2026/02/28 14:12:46 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)game->screen_width - 1;
	ray->ray_dir_x = game->dir_x + game->plane_x * ray->camera_x;
	ray->ray_dir_y = game->dir_y + game->plane_y * ray->camera_x;
	ray->map_x = (int)game->pos_x;
	ray->map_y = (int)game->pos_y;
	ray->delta_dist_x = (ray->ray_dir_x == 0) * 1e30
		+ (ray->ray_dir_x != 0) * fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = (ray->ray_dir_y == 0) * 1e30
		+ (ray->ray_dir_y != 0) * fabs(1 / ray->ray_dir_y);
	ray->step_x = (ray->ray_dir_x < 0) * -1 + (ray->ray_dir_x >= 0);
	ray->step_y = (ray->ray_dir_y < 0) * -1 + (ray->ray_dir_y >= 0);
	ray->side_dist_x = (ray->ray_dir_x < 0) * (game->pos_x - ray->map_x)
		* ray->delta_dist_x + (ray->ray_dir_x >= 0)
		* (ray->map_x + 1.0 - game->pos_x) * ray->delta_dist_x;
	ray->side_dist_y = (ray->ray_dir_y < 0) * (game->pos_y - ray->map_y)
		* ray->delta_dist_y + (ray->ray_dir_y >= 0)
		* (ray->map_y + 1.0 - game->pos_y) * ray->delta_dist_y;
	ray->hit = 0;
}

static void	cast_ray_until_hit(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->world_map[ray->map_x][ray->map_y] > 0)
			ray->hit = 1;
	}
}

static void	compute_wall_slice(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->pos_x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->pos_y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
	ray->line_height = (int)(game->screen_height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + game->screen_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->screen_height / 2;
	if (ray->draw_end >= game->screen_height)
		ray->draw_end = game->screen_height - 1;
	ray->color = 0xFF0000;
	if (ray->side == 1)
		ray->color /= 2;
}

static void	draw_wall_column(t_game *game, t_ray *ray, int x)
{
	int				y;
	int				tex_y;
	unsigned int	color;
	double			step;
	double			tex_pos;
	t_img			*tex;

	tex = &game->texture[get_texture_index(ray)];
	calculate_texture_coords(game, ray, tex);

	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - game->screen_height / 2
				+ ray->line_height / 2) * step;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= tex->height)  // clamp to avoid overflow
			tex_y = tex->height - 1;
		tex_pos += step;

		color = get_tex_pixel(tex, ray->tex_x, tex_y);
		// Optional shading for side hits
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;  // darken

		// Write to image buffer (your put_pixel or direct memory)
		char *dst = game->img.addr + (y * game->img.line_length
					+ x * (game->img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
		y++;
	}
}

void	render_frame(t_game *game)
{
	int		x;
	t_ray	ray;

	draw_background(game);
	x = 0;
	while (x < game->screen_width)
	{
		init_ray(game, &ray, x);
		cast_ray_until_hit(game, &ray);
		compute_wall_slice(game, &ray);
		draw_wall_column(game, &ray, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
