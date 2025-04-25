/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:04:47 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/25 18:54:37 by gd-auria         ###   ########.fr       */
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
#define PI_FIX 0.00000001
#define EPSILON 1e-9

#define INCREMENT_X 1
#define INCREMENT_Y 0

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

#define SHOW_WITH_COLORS 1

#define  NUM_OF_RAYS 1000

#define CAMERA_DISTANCE 20

#define SCALE_FACTOR 10000


typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_bras_params
{
	t_point	xy0;
	t_point	dx;
	t_point	sx;
	int		color;
}	t_bras_params;


typedef struct s_fov
{
	double	angle;
	double	half_left;
	double	half_right;
}	t_fov;



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
	int		orientation;
	t_point	first_side_point;
	t_point	first_impact_point;
	t_point	delta;
	t_point	path;
	t_point	spawn_point;
	t_point	end_point;
	int		last_increment;
	double	height_wall_line;
	double	x_wall_line;
	t_point	point_projection;
	double	len_projection;


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
	double		rotate_right;
	double		rotate_left;
	t_fov		fov;
	t_ray		ray;

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
	char	*floor_color;
	char	*ceiling_color;
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
void initialization(t_cube *cube);
void	point_init(t_point *point_to_initialize);
void define_map(t_cube *cube, char *path_of_map);
void define_windows(t_cube *cube);
void define_textures(t_cube *cube);
void visualize_in_2d(t_cube *cube);
void visualize_in_3d(t_cube *cube);
void define_hook_loop(t_cube *cube);
void check_map_closed(t_cube *cube, char **map_lines);
void exit_message(t_cube *cube, char *message);
int	update_movement(void *param);
t_point	find_tile(t_point point);
int	key_press(int keycode, void *param);
int	key_release(int keycode, void *param);
int	destroy(t_cube *cube);
int	step_management(t_player *player, int foot_step_decrement);
int	is_collision(double player_next_x, double player_next_y, t_cube *cube);
void	drawing_routine(t_cube *cube);
void	move_player_mains(int direction, t_move move, t_point *position, int step_decr);
void	move_player_oblq(int direction, t_move move, t_point *position, int step_decr);
int	get_direction(double perpendicular_direction);
void	drawing_routine(t_cube *cube);
t_point	chose_side_point(t_point spawn_point, int cardinal_direction);
t_point	calculate_path(t_point delta, double alpha);
t_point	calc_delta(t_point spawn_point, t_point second_point, int direction);
t_point	calculate_end_point(t_ray *ray, double alpha, t_cube *c3d);
t_point	trigonometric_point_calc(t_point point, double path, double alpha);

t_ray	dda(t_point start_point, double alpha, t_cube *c3d);
int	is_it_passing_between_two_walls(t_ray *ray, char **map_grid, t_point p);
int	is_it_a_wall(t_point point_to_verify, char **map_grid);
int	get_cardinal_direction(double angle);
int	is_it_inside_map_perimeter(t_point point, int width, int height);
void	initialize_ray(t_ray *ray);

int	north(int x, int y, t_cube *cube);
int	n_corner(int x, int y, t_cube *cube);
int	west(int x, int y, t_cube *cube);
void	draw_3d_scene(t_cube *cube);
void	draw_3d_fov(t_cube *cube);


void	put_pixel(t_image *img, int x, int y, int color);
int	get_color_in_hex(char *color);

t_point	find_intersection(t_point p1, double p1_ang, t_point p2, double p2_ang);
double	pitagora_theorem(t_point spawn_point, t_point second_point);

void	bresenham(t_cube *cube, int x1, int y1, int color);

int	get_pixel(t_image *image, int x, int y);
double	calculate_3d_wall_height(t_player player);

double	find_x_3d(double ray_angle, double fov_left_ray, double win_width);
int	find_x_texture(t_point impact_point, t_ray ray);
