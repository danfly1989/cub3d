/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 13:40:30 by daflynn           #+#    #+#             */
/*   Updated: 2026/02/28 14:13:48 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <stdlib.h>

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	int		tex_x;
}	t_ray;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	int		screen_width;
	int		screen_height;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		world_map[24][24];
	t_img	img;
	t_img	texture[4];
}	t_game;

int		handle_keypress(int keycode, t_game *game);
int		handle_close(t_game *game);
void	init_game(t_game *game);
void	init_world_map(t_game *game);
void	render_frame(t_game *game);
void	draw_background(t_game *game);
void	load_textures(t_game *game);
int		get_texture_index(t_ray *ray);
void	calculate_texture_coords(t_game *game, t_ray *ray, t_img *tex);
unsigned int	get_tex_pixel(t_img *tex, int x, int y);

#endif
