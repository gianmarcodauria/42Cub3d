/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_windows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:08:27 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/28 17:18:42 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	windows_size(t_window *window_2d, t_window *window_3d, \
int file_map_width, int file_map_height)
{
	window_2d->width = 64 * file_map_width;
	window_2d->height = 64 * file_map_height;
	window_3d->width = 64 * file_map_width;
	window_3d->height = 64 * file_map_height;
	if (window_2d->width > 1000)
		window_2d->width = 1000;
	if (window_2d->height > 1000)
		window_2d->height = 1000;
	if (window_3d->width > 1000)
		window_3d->width = 1000;
	if (window_3d->height > 1000)
		window_3d->height = 1000;
}

void	define_windows(t_cube *cube)
{
	windows_size(&cube->window_2d, &cube->window_3d, cube->file_map.width,
		cube->file_map.height);
	cube->connection = mlx_init();
	if (IS_2D == 1)
		cube->window_2d.ptr = mlx_new_window(cube->connection,
				cube->window_2d.width, cube->window_2d.height, "window_2d");
	cube->window_3d.ptr = mlx_new_window(cube->connection,
			cube->window_3d.width, cube->window_3d.height, "window_3d");
}
