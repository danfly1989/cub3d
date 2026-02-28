/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 13:40:30 by daflynn           #+#    #+#             */
/*   Updated: 2026/02/28 15:52:13 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

/*
** Texture indices — must match get_texture_index() in texture_utils.c
**   0 = North  (ray_dir_y < 0, side == 1)
**   1 = South  (ray_dir_y > 0, side == 1)
**   2 = East   (ray_dir_x > 0, side == 0)
**   3 = West   (ray_dir_x < 0, side == 0)
*/

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
	char	**map;
	int		map_width;
	int		map_height;
	char	*tex_path[4];
	int		floor_color;
	int		ceil_color;
	t_img	img;
	t_img	texture[4];
}	t_game;

/* ── render ─────────────────────────────────────────────────────────────── */
int				handle_keypress(int keycode, t_game *game);
int				handle_close(t_game *game);
void			init_game(t_game *game);
void			render_frame(t_game *game);
void			draw_wall_column(t_game *game, t_ray *ray, int x);
void			draw_background(t_game *game);
void			load_textures(t_game *game);
int				get_texture_index(t_ray *ray);
void			calculate_texture_coords(t_game *game, t_ray *ray, t_img *tex);
unsigned int	get_tex_pixel(t_img *tex, int x, int y);
int				is_wall(t_game *game, int x, int y);

/* ── parser ──────────────────────────────────────────────────────────────── */
void			parse_cub_file(t_game *game, char *path);
void			parse_meta_line(t_game *game, char *line);
int				is_meta_complete(t_game *game);
void			parse_map_section(t_game *game, char **lines, int start);
void			validate_map(t_game *game);
void			set_player_spawn(t_game *game);
void			parse_error(char *msg);
char			**parse_read_lines(char *path);
void			free_lines(char **lines);
void			cleanup(t_game *game);

#endif
