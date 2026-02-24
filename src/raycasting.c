/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:32:52 by daflynn           #+#    #+#             */
/*   Updated: 2026/02/24 18:32:54 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

// raycasting.c
#include "mlx.h"

void draw_background(void *mlx, void *win, int screenWidth, int screenHeight)
{
    for (int y = 0; y < screenHeight; y++)
    {
        for (int x = 0; x < screenWidth; x++)
        {
            if (y < screenHeight / 2)
                mlx_pixel_put(mlx, win, x, y, 0x87CEEB); // ceiling: light blue
            else
                mlx_pixel_put(mlx, win, x, y, 0x228B22); // floor: forest green
        }
    }
}