/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:58:12 by iakry             #+#    #+#             */
/*   Updated: 2022/12/08 02:09:20 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>


# define TILE_SIZE 64

# define MAP_NUM_ROWS 13
# define MAP_NUM_COLS 20

# define MINI_MAP 0.1

# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)
# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)

# define FOV_ANGL (60 * (PI / 180))
# define NUM_RAYS WINDOW_WIDTH

# define PROJECT_DIST ((WINDOW_WIDTH / 2) / tan(FOV_ANGL / 2))

# define NUM_TEXT 2
# define NUM_SPRT 2

# define PI 3.1415926530
# define TWO_PI 6.28318530

# define TEX_WITH 64
# define TEX_HEIGHT 64
# define NUM_TEXTURES 1

typedef struct s_img
{
    void	*img;
	char	*imgAddr;
	int		bitsPerPixel;
	int		lineLength;
	int		endian;
}   t_img;

typedef struct s_ray
{
    double rayAngle;
    double wallHitX;
    double wallHitY;
    double distance;
    int isHitVertical;
    int isRayUp;
    int isRayDown;
    int isRayLeft;
    int isRayRight;
    int wallContent;
}   t_ray;

typedef struct s_texture
{
    int        width;
    int        height;
    void    *img;
    char    *path;
}   t_texture;

typedef struct s_inter
{
    int is_ray_down;
    int is_ray_up;
    int is_ray_right;
    int is_ray_left;
    double x_inter, y_inter;
    double x_step, y_step;
    int horz_wall_hit;
    double horz_wall_hit_x;
    double horz_wall_hit_y;
    double next_touch_x;
    double next_touch_y;
    double x_tocheck;
    double y_tocheck;
    int horz_wall_content;
    int vert_wall_hit;
    double vert_wall_hit_x;
    double vert_wall_hit_y;
    int vert_wall_content;
} t_inter;

// typedef struct	s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }				t_data;

typedef struct s_var
{
    void *mlxPtr;
    void *winPtr;
    t_img	img;
    t_img   imgTmp;
    t_img   gg;
    double x;
    double y;
    double width;
    double height;
    int turnDirection;
    int walkDirection;
    double rotationAngle;
    double walkSpeed;
    double turnSpeed;
    unsigned int *texture[NUM_TEXTURES];
    t_inter inter;
    t_ray *ray;
  //  t_data *data;
    t_texture *text;
}   t_var;

// init
int initWindow(t_var *var);
int initImg(t_var *var);
int init(t_var *var);

// Utils
int wallCollision(double x, double y);
void setup(t_var *p);
int update(int key, t_var *var);
int keys(int key, t_var *var);

// utils 2

// Render
void renderminimap(t_var *var);
void renderMap(t_var *var);
void renderPlayer(t_var *var);
void drawSquare(t_var *var, int tileX, int tileY, int tileCol);
void drawDirLine(t_var *var, int beginX, int beginY, int endX, int endY, int color);

// Render utils
void setray(t_var *var);
void drawDirLine(t_var *var, int beginX, int beginY, int endX, int endY, int color);
void drawSquare(t_var *var, int tileX, int tileY, int tileCol);

// Castrays
double horz(t_var *var, double rayAngle);
double vert(t_var *var, double rayAngle);
void raydirection(t_var *var, double rayangle);
void cast(t_var *var, double rayAngle, int id);
void castRays(t_var *var);
int movePlayer(t_var *var);

// Castrays utils
double normAngle(double angle);
int map_has_wall(double x, double y);
double point_distance(double x1, double y1, double x2, double y2);
void updatevar(t_var *var);

// 3d projection
void render3Dprojection(t_var *var);
void project3d(t_var *var, int id, double top, double bottom, int wall_height);
void clear_img(t_var *var);
void	my_mlx_pixel_put(t_var *var, int x, int y, int color);

#endif