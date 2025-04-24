/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2dmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:10:13 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/24 21:15:54 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_step(t_bras_params *params, int x1, int y1)
{
	if (params->xy0.x < x1)
		params->sx.x = 1;
	else
		params->sx.x = -1;
	if (params->xy0.y < y1)
		params->sx.y = 1;
	else
		params->sx.y = -1;
}

void	draw_bras_line(t_cube *cube, t_bras_params *p, int x1, int y1)
{
	int	err;
	int	e2;

	err = p->dx.x - p->dx.y;
	while (1)
	{
		mlx_pixel_put(cube->connection, cube->window_2d.ptr, \
		p->xy0.x, p->xy0.y, p->color);
		if (p->xy0.x == x1 && p->xy0.y == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -(p->dx.y))
		{
			err -= p->dx.y;
			p->xy0.x += p->sx.x;
		}
		if (e2 < p->dx.x)
		{
			err += p->dx.x;
			p->xy0.y += p->sx.y;
		}
	}
}

void	bresenham(t_cube *cube, int x1, int y1, int color)
{
	t_bras_params	params;

	params.xy0.x = cube->player.position.x;
	params.xy0.y = cube->player.position.y;
	params.dx.x = fabs(x1 - params.xy0.x);
	params.dx.y = fabs(y1 - params.xy0.y);
	params.color = color;
	set_step(&params, x1, y1);
	draw_bras_line(cube, &params, x1, y1);
}

void	draw_2d_fov_boundaries(t_cube *cube)
{
	t_point	end_point;
	t_ray	ray;

	point_init(&end_point);

	ray = dda(cube->player.position, cube->player.fov.half_left, cube);
	end_point = ray.end_point;

	bresenham(cube, end_point.x, end_point.y, RED);
	ray = dda(cube->player.position, cube->player.fov.half_right, cube);

	end_point = ray.end_point;
	bresenham(cube, end_point.x, end_point.y, RED);
}

void	put_pixel(t_image *img, int x, int y, int color)
{
	int	*pixel;

	if (y < 0 || x < 0)
		return ;
	pixel = (int *)(img->data_addr + \
	(y * img->size_line + x * (img->bits_x_pixel / 8)));
	*pixel = color;
}

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

				put_pixel(&cube->map_image, cube->player.position.x + point.x, cube->player.position.y + point.y, BLACK);
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

	cube->map_image.ptr = mlx_new_image(cube->connection, cube->file_map.width * 64, cube->file_map.height * 64);
	cube->map_image.data_addr = mlx_get_data_addr(cube->map_image.ptr , &cube->map_image.bits_x_pixel,  &cube->map_image.size_line,  &cube->map_image.endian);

	draw_2d_map(&cube->map_image, cube);
	draw_player_in_img(cube);
	mlx_put_image_to_window(cube->connection, cube->window_2d.ptr, cube->map_image.ptr, 0, 0);
	draw_2d_fov_boundaries(cube);
}
