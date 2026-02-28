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
#include "parse_file_utils.h"

void	free_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
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
