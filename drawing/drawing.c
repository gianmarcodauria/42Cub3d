/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:40:31 by ccalabro          #+#    #+#             */
/*   Updated: 2025/04/28 16:40:34 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	drawing_routine(t_cube *cube)
{
	if (IS_2D)
	{
		mlx_destroy_image(cube->connection, cube->map_image.ptr);
		visualize_in_2d(cube);
	}
	mlx_destroy_image(cube->connection, cube->scene3d.ptr);
	draw_3d_scene(cube);
}

int	get_pixel(t_image *image, int x, int y)
{
	int	*pixel;

	if (x < 0 || x > image->width || y < 0 || y > image->height)
		return (RED);
	pixel = (int *)(image->data_addr + \
	(y * image->size_line + x * (image->bits_x_pixel / 8)));
	return (*pixel);
}
