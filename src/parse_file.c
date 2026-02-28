/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:00:00 by daflynn           #+#    #+#             */
/*   Updated: 2026/02/28 16:00:00 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
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

static void	normalize_line(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\r')
		line[len - 1] = '\0';
}

static void	set_split_line(char **lines, char *content, int *p)
{
	lines[p[2]] = ft_substr(content, p[0], p[1] - p[0]);
	normalize_line(lines[p[2]]);
	p[2]++;
	p[0] = p[1] + 1;
}

static char	**split_lines(char *content)
{
	char	**lines;
	int		p[3];

	p[2] = 1;
	p[1] = 0;
	while (content[p[1]])
		p[2] += (content[p[1]++] == '\n');
	lines = ft_calloc(p[2] + 1, sizeof(char *));
	if (!lines)
		return (NULL);
	p[0] = 0;
	p[1] = 0;
	p[2] = 0;
	while (content[p[1]])
	{
		if (content[p[1]] == '\n')
			set_split_line(lines, content, p);
		p[1]++;
	}
	lines[p[2]] = ft_strdup(content + p[0]);
	normalize_line(lines[p[2]]);
	return (lines);
}

char	**parse_read_lines(char *path)
{
	int		fd;
	char	*content;
	char	**lines;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		parse_error("Cannot open .cub file");
	content = read_all(fd);
	close(fd);
	if (!content)
		parse_error("Failed to read file");
	lines = split_lines(content);
	free(content);
	return (lines);
}
