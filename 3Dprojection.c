/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3Dprojection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:06:52 by iakry             #+#    #+#             */
/*   Updated: 2022/12/08 16:25:24 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_var *var, int x, int y, int color)
{
	char	*dst;

	dst = var->imgTmp.imgAddr + (y * var->imgTmp.lineLength + x * (var->imgTmp.bitsPerPixel / 8));
    *(unsigned int*)dst = color;
}

// void	my_mlx_pixel_put_l(t_var *var, int x, int y, int color)
// {
// 	char	*dst;
 
// 	dst = var->gg.imgAddr + (y * var->gg.lineLength + x * (var->gg.bitsPerPixel / 8));
// 	printf("===> {%p} \n", &color);
// 	printf("===> {%p} \n", dst);
//     *(unsigned int*)dst = color;
// }

void clear_img(t_var *var)
{
    int x = -1, y = -1;
    while (++x < WINDOW_WIDTH) {
        
        y = -1;
        while (++y < WINDOW_HEIGHT)
        {
            my_mlx_pixel_put(var, x, y, 0x00000000);
        }
    }
}

void project3d(t_var *var, int id, double top, double bottom, int wall_height)
{
    (void)wall_height;
    int y;
    unsigned int *waltexture;
    waltexture = (unsigned int *)malloc(sizeof(unsigned int) * (unsigned int)TEX_WITH * (unsigned int) TEX_HEIGHT);
  
    y = 0;
    while (y  < top)
        my_mlx_pixel_put(var, id, y++, 0x0000BBFF);
    y = top;
    
    int textureoffsetx;
    if (var->ray[id].isHitVertical)
        textureoffsetx = (int)var->ray[id].wallHitY % TILE_SIZE;
    else
        textureoffsetx = (int)var->ray[id].wallHitX % TILE_SIZE;
    while(y < bottom) 
    {
        int distancefromtop = y + (wall_height / 2) - (WINDOW_HEIGHT / 2);
        int textureoffsety = distancefromtop* ((double)TEX_HEIGHT / wall_height);
        char *texelcolor = var->gg.imgAddr + (textureoffsety * var->gg.lineLength + textureoffsetx * (var->gg.bitsPerPixel / 8));
        my_mlx_pixel_put(var, id, y++, (int )texelcolor);
        //y++;
       // }
        // Textures HERE!!!!!!!!!!!!!!!!!!!!!!!!!!
        
        // if (var->ray[id].isHitVertical)
        //     my_mlx_pixel_put(var, id, y++, 0x00FFFFFF);
        // else
        //     my_mlx_pixel_put(var, id, y++, 0x00CCCCCC);
    }
    while (y < WINDOW_HEIGHT)
        my_mlx_pixel_put(var, id, y++,  0x00CCCCCC);
}

void render3Dprojection(t_var *var)
{
    double corr_distance, proj_wall_height;
    int wall_height, wall_top_pixel, wall_bottom_pixel;
    int i = -1;

    clear_img(var);
    castRays(var);
    while (++i < NUM_RAYS)
    {
        corr_distance = var->ray[i].distance * cos(var->ray[i].rayAngle - var->rotationAngle); // corrected distance
        proj_wall_height = (TILE_SIZE / corr_distance) * PROJECT_DIST;
        wall_height = (int)proj_wall_height;
        wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_height / 2);
        if (wall_top_pixel < 0) 
            wall_top_pixel = 0;
        wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (wall_height / 2);
        if (wall_bottom_pixel > WINDOW_HEIGHT)
            wall_bottom_pixel = WINDOW_HEIGHT;
        project3d(var, i, wall_top_pixel, wall_bottom_pixel, wall_height);
    }
}