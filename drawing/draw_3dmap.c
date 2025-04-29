/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:47:06 by ccalabro          #+#    #+#             */
/*   Updated: 2025/04/29 15:19:16 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color_in_hex(char *color)
{
	int		r;
	int		g;
	int		b;
	char	**splitted;

	splitted = ft_split(color, ',');
	r = ft_atoi(splitted[0]);
	g = ft_atoi(splitted[1]);
	b = ft_atoi(splitted[2]);
	ft_free_matrix(splitted, -1);
	return (r << 16 | g << 8 | b);
}

/*remember that the coordinates of y go greater down*/
void	draw_floor(t_cube *cube)
{
	int	x;
	int	y;

	x = 0;
	y = cube->window_3d.height / 2;
	while (y < cube->window_3d.height)
	{
		x = 0;
		while (x < cube->window_3d.width)
		{
			put_pixel(&cube->scene3d, x, y, BLACK);
			x++;
		}
		y++;
	}
}

void	draw_ceiling(t_cube *cube)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < (cube->window_3d.height) / 2)
	{
		x = 0;
		while (x < cube->window_3d.width)
		{
			put_pixel(&cube->scene3d, x, y, \
			BLUE);
			x++;
		}
		y++;
	}
}

/*disegna la scena 3d: ovvero mette tutto nello stringone:
prima il cielo, poi la terra, e poi i muri...*/
void	draw_3d_scene(t_cube *cube)
{
	cube->scene3d.width = cube->window_3d.width;
	cube->scene3d.height = cube->window_3d.height;
	cube->scene3d.ptr = mlx_new_image(cube->connection, \
	cube->window_3d.width, cube->window_3d.height);
	cube->scene3d.data_addr = mlx_get_data_addr(cube->scene3d.ptr, \
	&cube->scene3d.bits_x_pixel, &cube->scene3d.size_line, \
	&cube->scene3d.endian);
	draw_floor(cube);
	draw_ceiling(cube);
	draw_3d_fov(cube);
	mlx_put_image_to_window(cube->connection, \
	cube->window_3d.ptr, cube->scene3d.ptr, 0, 0);
}
