/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:04:47 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/23 16:44:38 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//#include "mlx.h"
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

#define RADIUS 2

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

typedef struct s_player
{
	t_point		position;
	t_point		tile;


	int			cardinal_direction;
	double		direction;
	double		perpendicular_direction;
	double		rotate_alpha_right;
	double		rotate_alpha_left;


}	t_player;


typedef struct s_map
{
	int		width;
	int		height;
	char	*texture_data;
	char	*map_data;
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


