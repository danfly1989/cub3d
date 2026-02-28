/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 00:00:00 by daflynn           #+#    #+#             */
/*   Updated: 2026/02/28 00:00:00 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

static void	parse_lines(t_game *game, char **lines)
{
	int	i;
	int	map_start;

	i = 0;
	while (lines[i] && !is_meta_complete(game))
	{
		if (lines[i][0] != '\0')
			parse_meta_line(game, lines[i]);
		i++;
	}
	if (!is_meta_complete(game))
		parse_error("Missing required identifiers (need NO SO WE EA F C)");
	map_start = i;
	while (lines[map_start] && lines[map_start][0] == '\0')
		map_start++;
	if (!lines[map_start])
		parse_error("No map found in file");
	parse_map_section(game, lines, map_start);
}

void	parse_cub_file(t_game *game, char *path)
{
	char	**lines;

	if (ft_strlen(path) < 5
		|| ft_strncmp(path + ft_strlen(path) - 4, ".cub", 4) != 0)
		parse_error("File must have .cub extension");
	lines = parse_read_lines(path);
	if (!lines)
		parse_error("Failed to parse file lines");
	parse_lines(game, lines);
	free_lines(lines);
	validate_map(game);
	set_player_spawn(game);
}
