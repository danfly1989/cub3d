/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:24:33 by daflynn           #+#    #+#             */
/*   Updated: 2026/02/28 16:24:35 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parse_map_utils.h"

int	count_map_rows(char **lines, int start)
{
	int	count;

	count = 0;
	while (lines[start + count] && lines[start + count][0] != '\0')
		count++;
	return (count);
}

void	set_map_width(t_game *game)
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

void	set_ns_direction(t_game *game, char c)
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

void	set_player_direction(t_game *game, char c)
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
