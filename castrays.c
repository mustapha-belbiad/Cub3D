/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castrays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:30:23 by iakry             #+#    #+#             */
/*   Updated: 2022/12/08 15:38:28 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char mapp[MAP_NUM_ROWS][MAP_NUM_COLS] =  {"11111111111111111111",
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

void horz_inter(t_var *var, double rayangle)
{
    var->inter.y_inter = floor(var->y / TILE_SIZE) * TILE_SIZE;
    var->inter.y_inter += var->inter.is_ray_down ? TILE_SIZE : 0;

    var->inter.x_inter = var->x + (var->inter.y_inter - var->y) / tan(rayangle);
}

void horz_step(t_var *var, double rayangle)
{
    var->inter.y_step = TILE_SIZE;
    if (var->inter.is_ray_up)
        var->inter.y_step *= -1;

    var->inter.x_step = TILE_SIZE / tan(rayangle);
    if (var->inter.is_ray_left && var->inter.x_step > 0)
        var->inter.x_step *= -1;
    if (var->inter.is_ray_right && var->inter.x_step < 0)
        var->inter.x_step *= -1;
}

double horz(t_var *var, double rayAngle)
{
    horz_inter(var, rayAngle);
    horz_step(var, rayAngle);

    var->inter.next_touch_x = var->inter.x_inter;
    var->inter.next_touch_y = var->inter.y_inter;
    while (var->inter.next_touch_x >= 0 && var->inter.next_touch_x <= WINDOW_WIDTH && var->inter.next_touch_y >= 0 && var->inter.next_touch_y <= WINDOW_HEIGHT)
    {
        var->inter.x_tocheck = var->inter.next_touch_x;
        var->inter.y_tocheck = var->inter.next_touch_y;
        if (var->inter.is_ray_up)
            var->inter.y_tocheck += -1;
        
        if (map_has_wall(var->inter.x_tocheck, var->inter.y_tocheck)) {
            var->inter.horz_wall_hit_x = var->inter.next_touch_x;
            var->inter.horz_wall_hit_y = var->inter.next_touch_y;
            var->inter.horz_wall_content = mapp[(int)floor(var->inter.y_tocheck / TILE_SIZE)][(int)floor(var->inter.x_tocheck / TILE_SIZE)];
            var->inter.horz_wall_hit = 1;
            break;
        } else {
            var->inter.next_touch_x += var->inter.x_step;
            var->inter.next_touch_y += var->inter.y_step;
        }
    }
    if (var->inter.horz_wall_hit)
        return (point_distance(var->x, var->y, var->inter.horz_wall_hit_x, var->inter.horz_wall_hit_y));
    else
        return (INT_MAX);
}

void vert_inter(t_var *var, double rayangle)
{
    var->inter.x_inter = floor(var->x / TILE_SIZE) * TILE_SIZE;
    if (var->inter.is_ray_right)
        var->inter.x_inter += TILE_SIZE;

    var->inter.y_inter = var->y + (var->inter.x_inter - var->x) * tan(rayangle);
}

void vert_step(t_var *var, double rayangle)
{
    var->inter.x_step = TILE_SIZE;
    if (var->inter.is_ray_left)
        var->inter.x_step *= -1;

    var->inter.y_step = TILE_SIZE * tan(rayangle);
    if (var->inter.is_ray_up && var->inter.y_step > 0)
        var->inter.y_step *= -1;
    if (var->inter.is_ray_down && var->inter.y_step < 0)
        var->inter.y_step *= -1;
}

double vert(t_var *var, double rayAngle)
{
    vert_inter(var, rayAngle);
    vert_step(var, rayAngle);

    var->inter.next_touch_x = var->inter.x_inter;
    var->inter.next_touch_y = var->inter.y_inter;
    while (var->inter.next_touch_x >= 0 && var->inter.next_touch_x <= WINDOW_WIDTH && var->inter.next_touch_y >= 0 && var->inter.next_touch_y <= WINDOW_HEIGHT)
    {
        var->inter.x_tocheck = var->inter.next_touch_x;
        if (var->inter.is_ray_left)
            var->inter.x_tocheck += -1;
        var->inter.y_tocheck = var->inter.next_touch_y;
        if (map_has_wall(var->inter.x_tocheck, var->inter.y_tocheck)) {
            var->inter.vert_wall_hit_x = var->inter.next_touch_x;
            var->inter.vert_wall_hit_y = var->inter.next_touch_y;
            var->inter.vert_wall_content = mapp[(int)floor(var->inter.y_tocheck / TILE_SIZE)][(int)floor(var->inter.x_tocheck / TILE_SIZE)];
            var->inter.vert_wall_hit = 1;
            break;
        } else {
            var->inter.next_touch_x += var->inter.x_step;
            var->inter.next_touch_y += var->inter.y_step;
        }
    }
    if (var->inter.vert_wall_hit)
        return (point_distance(var->x, var->y, var->inter.vert_wall_hit_x, var->inter.vert_wall_hit_y));
    else
        return (INT_MAX);
}

void cast(t_var *var, double rayAngle, int id)
{
    double vertHitDistance = vert(var, rayAngle);
    double horzHitDistance = horz(var, rayAngle);

    if (vertHitDistance < horzHitDistance) {
        var->ray[id].distance = vertHitDistance;
        var->ray[id].wallHitX = var->inter.vert_wall_hit_x;;
        var->ray[id].wallHitY = var->inter.vert_wall_hit_y;
        var->ray[id].wallContent = var->inter.vert_wall_content;
        var->ray[id].isHitVertical = 1;
    } else {
        var->ray[id].distance = horzHitDistance;
        var->ray[id].wallHitX = var->inter.horz_wall_hit_x;;
        var->ray[id].wallHitY = var->inter.horz_wall_hit_y;
        var->ray[id].wallContent = var->inter.horz_wall_content;
        var->ray[id].isHitVertical = 0;
    }
    var->ray[id].rayAngle = rayAngle;
    var->ray[id].isRayDown = var->inter.is_ray_down;
    var->ray[id].isRayUp = var->inter.is_ray_up;
    var->ray[id].isRayLeft = var->inter.is_ray_left;
    var->ray[id].isRayRight = var->inter.is_ray_right;
}

void raydirection(t_var *var, double rayangle)
{
    if (rayangle >= 0 && rayangle < PI)
        var->inter.is_ray_down = 1;
    var->inter.is_ray_up = !var->inter.is_ray_down;
    if (rayangle <= 0.5 * PI || rayangle > 1.5 * PI)
        var->inter.is_ray_right = 1;
    var->inter.is_ray_left = !var->inter.is_ray_right;
}

void castRays(t_var *var)
{
    int id = -1;
    double rayangle;

    setray(var);
    movePlayer(var);
    while (++id < NUM_RAYS){
        rayangle = var->rotationAngle + atan((id - NUM_RAYS / 2) / PROJECT_DIST);
        rayangle = normAngle(rayangle);
        raydirection(var, rayangle);
        cast(var, rayangle, id);
        updatevar(var);
    }
}