/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castraysutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:32:15 by iakry             #+#    #+#             */
/*   Updated: 2022/12/04 22:28:37 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char mappi[MAP_NUM_ROWS][MAP_NUM_COLS] =  {"11111111111111111111",
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

double normAngle(double angle)
{
    angle = remainder(angle, TWO_PI);
    if (angle < 0)
        angle += TWO_PI;
    return angle;
}

int map_has_wall(double x, double y)
{
    return (mappi[(int)floor(y) / 64][(int)floor(x) / 64] == '1');
}

double point_distance(double x1, double y1, double x2, double y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void setray(t_var *var)
{
    int id = 0;
    while (id < NUM_RAYS){
        var->ray[id].rayAngle = 0;
        var->ray[id].wallHitX = 0;
        var->ray[id].wallHitY = 0;
        var->ray[id].distance = 0;
        var->ray[id].isHitVertical = 0;
        var->ray[id].isRayUp = 0;
        var->ray[id].isRayDown = 0;
        var->ray[id].isRayLeft = 0;
        var->ray[id].isRayRight = 0;
        var->ray[id].wallContent = 0;
        id++;
    }
}

void updatevar(t_var *var)
{
    var->inter.is_ray_down = 0;
    var->inter.is_ray_up = 0;
    var->inter.is_ray_right = 0;
    var->inter.is_ray_left = 0;
    var->inter.x_inter = 0;
    var->inter.y_inter = 0;
    var->inter.x_step = 0;
    var->inter.y_step = 0;
    var->inter.horz_wall_hit = 0;
    var->inter.horz_wall_hit_x = 0;
    var->inter.horz_wall_hit_y = 0;
    var->inter.horz_wall_content = 0;
    var->inter.vert_wall_hit = 0;
    var->inter.vert_wall_hit_x = 0;
    var->inter.vert_wall_hit_y = 0;
    var->inter.vert_wall_content = 0;
    var->inter.next_touch_x = 0;
    var->inter.next_touch_y = 0;
    var->inter.x_tocheck = 0;
    var->inter.y_tocheck = 0;
}