/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:30:26 by iakry             #+#    #+#             */
/*   Updated: 2022/12/08 15:23:30 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char map[MAP_NUM_ROWS][MAP_NUM_COLS] =  {"11111111111111111111",
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

int movePlayer(t_var *var)
{
    double moveStep;

    var->rotationAngle = var->turnDirection * var->turnSpeed * 0.3 + PI / 2;
    moveStep = var->walkDirection * var->walkSpeed * 0.1; // TODO: deltatime for speed

    double newX = var->x + cos(var->rotationAngle) * moveStep;
    double newY = var->y + sin(var->rotationAngle) * moveStep;

    if (!wallCollision(newX, newY)) {
        var->x = newX;
        var->y = newY;
        return 1;
    }
    return 0;
}

int game_play(t_var *var)
{
    render3Dprojection(var);
    renderminimap(var);

    var->img.img = var->imgTmp.img;
    mlx_put_image_to_window(var->mlxPtr, var->winPtr, var->img.img, 0, 0);
    return 1;
}

int mouse(int key, int x, int y, t_var *var)
{
    (void)x;
    (void)y;
    if (key == 1)
        var->turnDirection -= 1;
    if (key == 2)
        var->turnDirection += 1;
    return 1;
}

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    t_var var;
    var.ray = malloc(sizeof(t_ray) * NUM_RAYS);

    // if (checkargs)
        if (!init(&var))
            return 0;
    mlx_mouse_hook(var.winPtr, mouse, &var);
    mlx_hook(var.winPtr, 2, 0, keys, &var);
    mlx_hook(var.winPtr, 3, 0, update, &var);
    mlx_do_sync(var.mlxPtr);
     mlx_loop_hook(var.mlxPtr, game_play, &var);
    mlx_loop(var.mlxPtr);
    return 0;
}