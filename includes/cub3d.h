/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:04:47 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/23 22:51:54 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <math.h>
#include "libft.h"

#define IS_2D 1

#define RED 0xff0000
#define GRAY 0x808080
#define WHITE 0xffffff
#define BLACK 0X000000
#define YELLOW 0xffff00
#define PURPLE 0x800080
#define PINK 0xffc0cb
#define GREEN 0x00ff00
#define BLUE 0x0000ff

#define NE 13
#define E 15
#define SE 16
#define S 18
#define SW 19
#define W 21
#define NW 22
#define N 24

#define WW 119
#define SS 115
#define AA 97
#define DD 100
#define ESC 65307
#define LEFT 65361
#define RIGHT 65363

#define PI_G 3.14159265358979323846

#define FOV_ANGLE 1.25664

#define RADIUS 2

#define PEDEGREE 0.0785398163
#define  FOOT_JOB 5

#define CIRCUMFERENCE_CHECKS 8

#define TRUE 1
#define FALSE 0

//promemoria in caso vuoi cambiare nomi
typedef struct s_fov
{
	double	angle;
	double	half_left;
	double	half_right;
}	t_fov;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;


typedef struct s_dim
{
	int width;
	int	height;
}	t_dim;

typedef struct s_window
{
	void	*ptr;
	int		width;
	int		height;
}	t_window;


typedef struct s_ray
{
	int		cardinal_direction;
	t_point	first_side_point;
	t_point	first_impact_point;
	t_point	delta;
	t_point	path;
	t_point	first_point;

}	t_ray;

typedef struct s_move
{
	int	w;
	int	a;
	int	s;
	int	d;
}	t_move;

typedef struct s_player
{
	t_point		position;
	t_point		tile;
	t_move		move;
	int			cardinal_direction;
	double		direction;
	double		perpendicular_direction;
	double		rotate_alpha_right;
	double		rotate_alpha_left;
	t_fov		fov;

}	t_player;


typedef struct s_map
{
	int		width;
	int		height;
	char	*texture_data;
	char	*map_data;
	t_point	player_position;
	int		player_orientation;
	char	**grid;
}	t_map;

typedef struct s_image
{
	void	*ptr;
	char	*data_addr;
	int		size_line;
	int		bits_x_pixel;
	int		endian;
	int		width;
	int		height;
}	t_image;


typedef struct s_cube
{
	void	*connection;


	t_window	window_2d;
	t_window	window_3d;
	t_map		file_map;

	char		**map_lines;
	t_player	player;
	t_image		texture[4];
	t_image		scene3d;
	t_image		map_image;
}	t_cube;


//FUNCTIONS IN MAIN.C FILE

void parse_argc(int argc);
void initialize_cube(t_cube *cube);
void define_map(t_cube *cube, char *path_of_map);
void define_windows(t_cube *cube);
void define_textures(t_cube *cube);
void visualize_in_2d(t_cube *cube);
void visualize_in_3d(t_cube *cube);
void define_hook_loop(t_cube *cube);
void check_map_closed(t_cube *cube, char **map_lines);
void exit_message(t_cube *cube, char *message);
int	mov_key_press(int keycode, void *param);
int	update_movement(void *param);
t_point	find_tile(t_point point);
int	mov_key_release(int keycode, void *param);
int	on_destroy(t_cube *cube);
