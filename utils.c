/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:13:37 by iakry             #+#    #+#             */
/*   Updated: 2022/12/08 01:45:20 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char mapa[MAP_NUM_ROWS][MAP_NUM_COLS] =  {"11111111111111111111",
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

int wallCollision(double x, double y)
{
    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
        return 1;
    x = floor(x / TILE_SIZE);
    y = floor(y / TILE_SIZE);
    return (mapa[(int)y][(int)x] != '0');
}

void setup(t_var *var)
{
   // char *hola;

    var->x =  WINDOW_WIDTH / 2;
    var->y =  WINDOW_HEIGHT / 2;
    var->width = 5;
    var->height = 5;
    var->turnDirection = 0;
    var->walkDirection = 0;
    var->rotationAngle = PI / 2;
    var->walkSpeed = 30;
    var->turnSpeed = 45 * (PI / 180);
    // var->imgTmp.img =  mlx_xpm_file_to_image(var->mlxPtr, "wall2.xpm", &x, &y);
    // var->imgTmp.imgAddr = mlx_get_data_addr( var->imgTmp.img , &var->imgTmp.bitsPerPixel, &var->imgTmp.lineLength, &var->gg.endian);
    //var->texture[0] =  (unsigned int *)var->imgTmp.imgAddr;
    
}

int update(int key, t_var *var)
{
    if (key == 1 || key == 125)
        var->walkDirection = 0;
    if (key == 13 || key == 126)
        var->walkDirection = 0;
    return 1;
}

int keys(int key, t_var *var)
{
    if (key == 53) {
	    mlx_destroy_window(var->mlxPtr, var->winPtr);
	    exit(0);
    }
    if (key == 1 || key == 125) // up
        var->walkDirection -= 1;
    if (key == 13 || key == 126) // down
        var->walkDirection += 1;
    if (key == 0 || key == 123) // left
        var->turnDirection -= 1;
    if (key == 2 || key == 124) // right
        var->turnDirection += 1;
    return 0;
}
