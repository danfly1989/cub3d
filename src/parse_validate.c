/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 00:00:00 by daflynn           #+#    #+#             */
/*   Updated: 2026/02/28 00:00:00 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Returns 1 if (x, y) is within the map and is a non-space character.
** Used to verify that walkable cells are not adjacent to voids.
*/
static int	cell_is_solid(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || y >= game->map_height)
		return (0);
	if (x >= (int)ft_strlen(game->map[y]))
		return (0);
	return (game->map[y][x] != ' ');
}

/*
** Every '0' and spawn cell must have 4 solid neighbours.
** A single exposed side means the map is not enclosed.
*/
static void	check_enclosed(t_game *game)
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
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (!cell_is_solid(game, x - 1, y)
					|| !cell_is_solid(game, x + 1, y)
					|| !cell_is_solid(game, x, y - 1)
					|| !cell_is_solid(game, x, y + 1))
					parse_error("Map is not enclosed by walls");
			}
			x++;
		}
		y++;
	}
}

/*
** Verify every character in every map row is legal:
**   '0' '1' ' ' — floor, wall, void
**   'N' 'S' 'E' 'W' — player spawn directions
*/
static void	check_map_chars(t_game *game)
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
			if (c != '0' && c != '1' && c != ' '
				&& c != 'N' && c != 'S' && c != 'E' && c != 'W')
				parse_error("Invalid character in map");
			x++;
		}
		y++;
	}
}

/*
** Verify exactly one player spawn character exists in the map.
*/
static void	check_player_count(t_game *game)
{
	int		count;
	int		y;
	int		x;
	char	c;

	count = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			c = game->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				count++;
			x++;
		}
		y++;
	}
	if (count == 0)
		parse_error("No player spawn found in map");
	if (count > 1)
		parse_error("Multiple player spawns found in map");
}

void	validate_map(t_game *game)
{
	check_map_chars(game);
	check_player_count(game);
	check_enclosed(game);
}
