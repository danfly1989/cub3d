/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:34:25 by daflynn           #+#    #+#             */
/*   Updated: 2026/02/28 14:34:37 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>

int	get_texture_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (2);
		return (3);
	}
	if (ray->ray_dir_y > 0)
		return (1);
	return (0);
}

void	calculate_texture_coords(t_game *game, t_ray *ray, t_img *tex)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		ray->tex_x = tex->width - ray->tex_x - 1;
}

unsigned int	get_tex_pixel(t_img *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	load_textures(t_game *game)
{
	char	*paths[4];
	int		i;

	paths[0] = "textures/wall.xpm";
	paths[1] = "textures/wall.xpm";
	paths[2] = "textures/wall.xpm";
	paths[3] = "textures/wall.xpm";
	i = 0;
	while (i < 4)
	{
		game->texture[i].img = mlx_xpm_file_to_image(game->mlx, paths[i],
				&game->texture[i].width, &game->texture[i].height);
		if (!game->texture[i].img)
		{
			write(2, "Error: cannot load texture\n", 27);
			exit(1);
		}
		game->texture[i].addr = mlx_get_data_addr(game->texture[i].img,
				&game->texture[i].bits_per_pixel,
				&game->texture[i].line_length,
				&game->texture[i].endian);
		i++;
	}
}
