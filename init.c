/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:19:32 by iakry             #+#    #+#             */
/*   Updated: 2022/12/08 01:55:07 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int initWindow(t_var *var)
{
    if (!(var->mlxPtr = mlx_init()))
        return 0;
    if (!(var->winPtr = mlx_new_window(var->mlxPtr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d")))
        return 0;
    return 1;
}

int initImg(t_var *var)
{   
    int x = (int )WINDOW_WIDTH;
    int y = (int )WINDOW_HEIGHT;

    var->img.img = mlx_new_image(var->mlxPtr, WINDOW_WIDTH, WINDOW_HEIGHT);
    var->img.imgAddr = mlx_get_data_addr(var->img.img, &var->img.bitsPerPixel, &var->img.lineLength,
								&var->img.endian);
    var->imgTmp.img = mlx_new_image(var->mlxPtr, WINDOW_WIDTH, WINDOW_HEIGHT);
    var->imgTmp.imgAddr = mlx_get_data_addr(var->imgTmp.img, &var->imgTmp.bitsPerPixel, &var->imgTmp.lineLength,
								&var->imgTmp.endian);
     var->gg.img =  mlx_xpm_file_to_image(var->mlxPtr, "wall2.xpm", &x, &y);
    var->gg.imgAddr = mlx_get_data_addr( var->imgTmp.img , &var->imgTmp.bitsPerPixel, &var->imgTmp.lineLength, &var->gg.endian);
    // var->gg.img =  mlx_xpm_file_to_image(var->mlxPtr, "wall2.xpm", &x, &y);
    // var->gg.imgAddr = mlx_get_data_addr( var->gg.img , &var->gg.bitsPerPixel, &var->gg.lineLength, &var->gg.endian);
    // printf("{%s}\n", var->gg.imgAddr);
    // printf("{%s}\n", var->gg.img);
    return 1;
}

int init(t_var *var)
{
    if (initWindow(var))
        initImg(var);
    setup(var);
    return 1;
}