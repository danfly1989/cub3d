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

#include <stdlib.h>   // for exit()
#include <unistd.h>   // for write()
#include "mlx.h"      // for mlx_* functions (if not already in cub3d.h)
#include "cub3d.h"

int	get_texture_index(t_ray *ray)
{
	if (ray->side == 0) // vertical wall hit
	{
		if (ray->ray_dir_x > 0)
			return (2); // west face
		else
			return (3); // east face
	}
	else // horizontal wall hit
	{
		if (ray->ray_dir_y > 0)
			return (1); // south face
		else
			return (0); // north face
	}
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
	// Flip texture if needed to keep orientation consistent
	if ((ray->side == 0 && ray->ray_dir_x > 0) ||
	    (ray->side == 1 && ray->ray_dir_y < 0))
		ray->tex_x = tex->width - ray->tex_x - 1;
}

unsigned int	get_tex_pixel(t_img *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0); // fallback black
	dst = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	load_textures(t_game *game)
{
	char	*paths[4] = {
		"textures/wall.xpm",   // north
		"textures/wall.xpm",   // south
		"textures/wall.xpm",   // west
		"textures/wall.xpm"    // east
	};
	int		i;

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
