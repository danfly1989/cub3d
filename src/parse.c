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

static char	*read_all(int fd)
{
	char	buf[4096];
	char	*content;
	char	*tmp;
	int		n;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	n = read(fd, buf, 4095);
	while (n > 0)
	{
		buf[n] = '\0';
		tmp = ft_strjoin(content, buf);
		free(content);
		content = tmp;
		if (!content)
			return (NULL);
		n = read(fd, buf, 4095);
	}
	return (content);
}

static void	free_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}

static char	**split_lines(char *content)
{
	char	**lines;
	int		count;
	int		i;

	count = 1;
	i = 0;
	while (content[i])
		count += (content[i++] == '\n');
	lines = ft_calloc(count + 1, sizeof(char *));
	if (!lines)
		return (NULL);
	i = 0;
	count = 0;
	while (content[i])
	{
		if (content[i] == '\n')
		{
			lines[count] = ft_substr(content, 0, i);
			if (lines[count] && ft_strlen(lines[count]) > 0
				&& lines[count][ft_strlen(lines[count]) - 1] == '\r')
				lines[count][ft_strlen(lines[count]) - 1] = '\0';
			count++;
			content += i + 1;
			i = 0;
		}
		else
			i++;
	}
	lines[count] = ft_strdup(content);
	return (lines);
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
	int		fd;
	char	*content;
	char	**lines;

	if (ft_strlen(path) < 5
		|| ft_strncmp(path + ft_strlen(path) - 4, ".cub", 4) != 0)
		parse_error("File must have .cub extension");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		parse_error("Cannot open .cub file");
	content = read_all(fd);
	close(fd);
	if (!content)
		parse_error("Failed to read file");
	lines = split_lines(content);
	free(content);
	if (!lines)
		parse_error("Failed to parse file lines");
	parse_lines(game, lines);
	free_lines(lines);
	validate_map(game);
	set_player_spawn(game);
}