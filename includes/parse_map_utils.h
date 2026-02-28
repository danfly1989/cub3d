/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:40:39 by daflynn           #+#    #+#             */
/*   Updated: 2026/02/28 16:40:47 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MAP_UTILS_H
# define PARSE_MAP_UTILS_H

int		count_map_rows(char **lines, int start);
void	set_map_width(struct s_game *game); // or t_game if typedef exists
void	set_ns_direction(struct s_game *game, char c);
void	set_player_direction(struct s_game *game, char c);

#endif
