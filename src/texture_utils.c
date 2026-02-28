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

/*
** Map the hit wall face to a texture index.
**   side == 0  vertical wall   ray_dir_x > 0 → East (2), else West (3)
**   side == 1  horizontal wall ray_dir_y > 0 → South (1), else North (0)
*/
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

/*
** Load the four directional textures from paths parsed out of the .cub file.
** Order: 0=North 1=South 2=East 3=West — must match get_texture_index().
*/
void	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->texture[i].img = mlx_xpm_file_to_image(game->mlx,
				game->tex_path[i],
				&game->texture[i].width,
				&game->texture[i].height);
		if (!game->texture[i].img)
		{
			ft_putstr_fd("Error\nCannot load texture: ", 2);
			ft_putstr_fd(game->tex_path[i], 2);
			ft_putstr_fd("\n", 2);
			exit(1);
		}
		game->texture[i].addr = mlx_get_data_addr(game->texture[i].img,
				&game->texture[i].bits_per_pixel,
				&game->texture[i].line_length,
				&game->texture[i].endian);
		i++;
	}
}
