/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2dmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:10:13 by gd-auria          #+#    #+#             */
/*   Updated: 2025/05/06 15:43:54 by ccalabro         ###   ########.fr       */
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
