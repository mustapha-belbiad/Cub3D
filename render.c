/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:18:54 by iakry             #+#    #+#             */
/*   Updated: 2022/12/04 22:28:10 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char mappp[MAP_NUM_ROWS][MAP_NUM_COLS] =  {"11111111111111111111",
                                                "10000000000000010001",
                                                "10000000000000080001",
                                                "10000000000000000001",
                                                "10002203040506000001",
                                                "10000003000000000001",
                                                "10000003000000000001",
                                                "10000000000007000001",
                                                "10000000000000000005",
                                                "10000000000010000005",
                                                "10000000000010000005",
                                                "10000000000010000005",
                                                "11111111111111555555"};

void drawDirLine(t_var *var, int beginX, int beginY, int endX, int endY, int color)
{
    double deltaX = endX - beginX;
    double deltaY = endY - beginY;

    int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

    deltaX /= pixels;
    deltaY /= pixels;

    double pixelX = beginX;
    double pixelY = beginY;
    while (pixels)
    {
        my_mlx_pixel_put(var, pixelX * MINI_MAP, pixelY * MINI_MAP, color);
        pixelX += deltaX;
        pixelY += deltaY;
        --pixels;
    }
}

void drawSquare(t_var *var, int tileX, int tileY, int tileCol)
{
    double x;
    double y;

    y = tileY;
    while (y < tileY + TILE_SIZE){
        x = tileX - 1;
        while (++x < tileX + TILE_SIZE)
            my_mlx_pixel_put(var, x * MINI_MAP, y * MINI_MAP, tileCol);
        y++;
    }
}

void renderMap(t_var *var)
{
    int x = -1, y = -1;

    while (++y < MAP_NUM_ROWS)
    {
        x = -1;
        while (++x < MAP_NUM_COLS)
        {
            if (mappp[y][x] == '1')
                drawSquare(var, x * TILE_SIZE, y * TILE_SIZE, 0);
            else if (mappp[y][x] == '0')
                drawSquare(var, x * TILE_SIZE, y * TILE_SIZE, 0xFFFFFF);
        }
    }
}

void renderPlayer(t_var *var)
{
    double x = 0, y = 0;

    x = var->x;
    y = var->y;

    while (y < var->y + var->height){
        x = var->x;
        while (x < var->x + var->width){
            my_mlx_pixel_put(var, x * MINI_MAP, y * MINI_MAP, 255);
            x++;
        }
        y++;
    }
}

void renderminimap(t_var *var)
{
    renderMap(var);
    renderPlayer(var);
}