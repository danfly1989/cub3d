#include "mlx.h"
#include <stdlib.h>
#include <math.h>

void draw_background(void *mlx, void *win, int screenWidth, int screenHeight);

int main(void)
{
    void *mlx = mlx_init();
    if (!mlx) return (1);
    int screenWidth = 200;
    int screenHeight = 100;
    void *win = mlx_new_window(mlx, screenWidth, screenHeight, "Cub3D");
    if (!win) return (1);

    // player
    double posX = 22.0, posY = 12.0;
    double dirX = -1.0, dirY = 0.0;
    double planeX = 0.0, planeY = 0.66;

    // simple map
    int worldMap[24][24] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    // draw floor/ceiling first
    draw_background(mlx, win, screenWidth, screenHeight);

    // draw a single red wall slice in the middle for now
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

        int hit = 0;
        int side;
        while (!hit)
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
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }

        double perpWallDist = (side == 0)
            ? (mapX - posX + (1 - stepX) / 2) / rayDirX
            : (mapY - posY + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(screenHeight / perpWallDist);

        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        int color = 0xFF0000;
        if (side == 1) color /= 2;

        for (int y = drawStart; y < drawEnd; y++)
            mlx_pixel_put(mlx, win, x, y, color);
    }

    mlx_loop(mlx);
    return 0;
}