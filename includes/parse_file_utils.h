/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 17:10:00 by daflynn           #+#    #+#             */
/*   Updated: 2026/02/28 17:10:00 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_FILE_UTILS_H
# define PARSE_FILE_UTILS_H

char	*read_all(int fd);
void	normalize_line(char *line);
void	set_split_line(char **lines, char *content, int *p);
char	**split_lines(char *content);

#endif
