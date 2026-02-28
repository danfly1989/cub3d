/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 00:00:00 by daflynn           #+#    #+#             */
/*   Updated: 2026/02/28 00:00:00 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_tex_path(char **dest, char *src)
{
	if (*dest)
		parse_error("Duplicate texture identifier");
	while (*src == ' ')
		src++;
	if (*src == '\0')
		parse_error("Texture path is empty");
	*dest = ft_strdup(src);
	if (!*dest)
		parse_error("Memory allocation failed");
}

static void	free_split(char **parts)
{
	int	i;

	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
}

static int	parse_rgb(char *s)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	while (*s == ' ')
		s++;
	parts = ft_split(s, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		parse_error("Color must be exactly R,G,B with three values");
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	free_split(parts);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		parse_error("Color channel out of range (0-255)");
	return ((r << 16) | (g << 8) | b);
}

int	is_meta_complete(t_game *game)
{
	return (game->tex_path[0] && game->tex_path[1]
		&& game->tex_path[2] && game->tex_path[3]
		&& game->floor_color != -1 && game->ceil_color != -1);
}

void	parse_meta_line(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		set_tex_path(&game->tex_path[0], line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		set_tex_path(&game->tex_path[1], line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		set_tex_path(&game->tex_path[2], line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		set_tex_path(&game->tex_path[3], line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (game->floor_color != -1)
			parse_error("Duplicate F identifier");
		game->floor_color = parse_rgb(line + 2);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (game->ceil_color != -1)
			parse_error("Duplicate C identifier");
		game->ceil_color = parse_rgb(line + 2);
	}
	else
		parse_error("Unknown identifier in file");
}
