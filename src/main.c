// main.c
#include "mlx.h"
#include <stdlib.h>
#include <math.h>

void draw_background(void *mlx, void *win, int screenWidth, int screenHeight);

int main(void)
{
    void *mlx;
    void *win;
    int screenWidth = 200;
    int screenHeight = 100;

    mlx = mlx_init();
    if (!mlx)
        return (1);
    win = mlx_new_window(mlx, screenWidth, screenHeight, "Cub3D Test Wall");
    if (!win)
        return (1);

    double posX = 12.0, posY = 12.0; // move player away from edges
    double dirX = -1.0, dirY = 0.0;
    double planeX = 0.0, planeY = 0.66;

    int worldMap[24][24] = {0};

    // Create a full wall row in front of the player
    for (int i = 0; i < 24; i++)
        worldMap[10][i] = 1;  // row 10 is a wall

    draw_background(mlx, win, screenWidth, screenHeight);

    // simple raycasting loop to draw red wall
    for (int x = 0; x < screenWidth; x++)
    {
        double cameraX = 2 * x / (double)screenWidth - 1;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        int mapX = (int)posX;
        int mapY = (int)posY;

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        int stepX = (rayDirX < 0) ? -1 : 1;
        int stepY = (rayDirY < 0) ? -1 : 1;

        double sideDistX = (rayDirX < 0) ? (posX - mapX) * deltaDistX : (mapX + 1.0 - posX) * deltaDistX;
        double sideDistY = (rayDirY < 0) ? (posY - mapY) * deltaDistY : (mapY + 1.0 - posY) * deltaDistY;

        int hit = 0, side;
        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (worldMap[mapX][mapY] > 0)
                hit = 1;
        }

        double perpWallDist = (side == 0) ? (mapX - posX + (1 - stepX) / 2) / rayDirX
                                         : (mapY - posY + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(screenHeight / perpWallDist);
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        int color = 0xFF0000;
        if (side == 1)
            color /= 2;

        for (int y = drawStart; y < drawEnd; y++)
            mlx_pixel_put(mlx, win, x, y, color);
    }

    mlx_loop(mlx);
    return (0);
}