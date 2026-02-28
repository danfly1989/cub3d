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

static int	count_map_rows(char **lines, int start)
{
	int	count;

	count = 0;
	while (lines[start + count] && lines[start + count][0] != '\0')
		count++;
	return (count);
}

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

static void	set_ns_direction(t_game *game, char c)
{
	game->dir_x = 0;
	if (c == 'N')
	{
		game->dir_y = -1;
		game->plane_x = 0.66;
	}
	else
	{
		game->dir_y = 1;
		game->plane_x = -0.66;
	}
	game->plane_y = 0;
}

static void	set_player_direction(t_game *game, char c)
{
	if (c == 'N' || c == 'S')
		set_ns_direction(game, c);
	else
	{
		game->dir_y = 0;
		if (c == 'E')
		{
			game->dir_x = 1;
			game->plane_y = 0.66;
		}
		else
		{
			game->dir_x = -1;
			game->plane_y = -0.66;
		}
		game->plane_x = 0;
	}
}

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
				set_player_direction(game, c);
				game->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

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
