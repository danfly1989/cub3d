/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 00:00:00 by daflynn           #+#    #+#             */
/*   Updated: 2026/02/28 00:00:00 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Count consecutive non-NULL lines from index start.
** Per subject: map must be last element — any blank line ends the map.
*/
static int	count_map_rows(char **lines, int start)
{
	int	count;

	count = 0;
	while (lines[start + count] && lines[start + count][0] != '\0')
		count++;
	return (count);
}

/*
** Compute the width of the widest map row.
*/
static void	set_map_width(t_game *game)
{
	int	i;
	int	len;

	i = 0;
	game->map_width = 0;
	while (i < game->map_height)
	{
		len = ft_strlen(game->map[i]);
		if (len > game->map_width)
			game->map_width = len;
		i++;
	}
}

/*
** Set the player's starting position and direction from spawn char.
** Replaces the spawn character with '0' so raycasting treats it as floor.
*/
void	set_player_spawn(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			c = game->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->pos_x = x + 0.5;
				game->pos_y = y + 0.5;
				if (c == 'N') { game->dir_x = 0; game->dir_y = -1;
					game->plane_x = 0.66; game->plane_y = 0; }
				else if (c == 'S') { game->dir_x = 0; game->dir_y = 1;
					game->plane_x = -0.66; game->plane_y = 0; }
				else if (c == 'E') { game->dir_x = 1; game->dir_y = 0;
					game->plane_x = 0; game->plane_y = 0.66; }
				else { game->dir_x = -1; game->dir_y = 0;
					game->plane_x = 0; game->plane_y = -0.66; }
				game->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

/*
** Allocate game->map, copy each row from the parsed lines.
** map is NULL-terminated. map_height and map_width are set.
*/
void	parse_map_section(t_game *game, char **lines, int start)
{
	int	height;
	int	i;

	height = count_map_rows(lines, start);
	if (height == 0)
		parse_error("Map is empty");
	game->map = ft_calloc(height + 1, sizeof(char *));
	if (!game->map)
		parse_error("Memory allocation failed");
	game->map_height = height;
	i = 0;
	while (i < height)
	{
		game->map[i] = ft_strdup(lines[start + i]);
		if (!game->map[i])
			parse_error("Memory allocation failed");
		i++;
	}
	set_map_width(game);
}
