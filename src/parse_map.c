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
#include "parse_map_utils.h"

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
