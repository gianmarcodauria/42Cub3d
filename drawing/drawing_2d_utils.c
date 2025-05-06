/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_2d_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:43:06 by ccalabro          #+#    #+#             */
/*   Updated: 2025/05/06 15:43:39 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player_in_img(t_cube *cube)
{
	t_point	point;

	point.x = 0;
	point.y = 0;
	point.y = -RADIUS;
	while (point.y <= RADIUS)
	{
		point.x = -RADIUS;
		while (point.x <= RADIUS)
		{
			if (pow(point.x, 2) + pow(point.y, 2) <= RADIUS * RADIUS)
			{
				put_pixel(&cube->map_image, cube->player.position.x
					+ point.x, cube->player.position.y + point.y, BLACK);
			}
			point.x++;
		}
		point.y++;
	}
}

static void	draw_tile_with_marg(t_image *img, t_point xy, int color)
{
	int	x_value;
	int	y_value;

	x_value = xy.x;
	y_value = xy.y;
	while (xy.y < y_value + 64)
	{
		xy.x = x_value;
		while (xy.x < x_value + 64)
		{
			if (xy.y == y_value + 64 - 1)
				put_pixel(img, xy.x, xy.y, BLACK);
			else if (xy.x == x_value + 64 - 1)
				put_pixel(img, xy.x, xy.y, BLACK);
			else
				put_pixel(img, xy.x, xy.y, color);
			xy.x++;
		}
		xy.y++;
	}
}

void	draw_2d_map(t_image *img, t_cube *cube)
{
	int		x;
	int		y;
	t_point	xy;

	y = -1;
	while (++y < 0 + cube->file_map.height)
	{
		x = -1;
		while (++x < 0 + cube->file_map.width)
		{
			xy.x = x * 64;
			xy.y = y * 64;
			if (x >= ft_strlen(cube->file_map.grid[y]))
				draw_tile_with_marg(img, xy, BLACK);
			else if (cube->file_map.grid[y][x] == '1')
				draw_tile_with_marg(img, xy, GRAY);
			else if (cube->file_map.grid[y][x] == '0')
				draw_tile_with_marg(img, xy, WHITE);
			else if (cube->file_map.grid[y][x] == ' ')
				draw_tile_with_marg(img, xy, BLACK);
			else
				draw_tile_with_marg(img, xy, RED);
		}
	}
}

void	visualize_in_2d(t_cube *cube)
{
	cube->map_image.ptr = mlx_new_image(cube->connection,
			cube->file_map.width * 64, cube->file_map.height * 64);
	cube->map_image.data_addr = mlx_get_data_addr(cube->map_image.ptr,
			&cube->map_image.bits_x_pixel, &cube->map_image.size_line,
			&cube->map_image.endian);
	draw_2d_map(&cube->map_image, cube);
	draw_player_in_img(cube);
	mlx_put_image_to_window(cube->connection, cube->window_2d.ptr,
		cube->map_image.ptr, 0, 0);
	draw_2d_fov_boundaries(cube);
}
