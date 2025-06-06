/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:41:45 by gd-auria          #+#    #+#             */
/*   Updated: 2025/05/05 19:06:27 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	w3d_resize(t_cube *cube)
{
	mlx_destroy_image(cube->connection, cube->scene3d.ptr);
	draw_3d_scene(cube);
	return (0);
}

int	w2d_resize(t_cube *cube)
{
	mlx_destroy_image(cube->connection, cube->map_image.ptr);
	visualize_in_2d(cube);
	return (0);
}

void	define_hook_loop(t_cube *cube)
{
	mlx_hook(cube->window_3d.ptr, KeyPress, KeyPressMask,
		&key_press, cube);
	mlx_hook(cube->window_3d.ptr, KeyRelease, KeyReleaseMask,
		&key_release, cube);
	mlx_hook(cube->window_3d.ptr, DestroyNotify, StructureNotifyMask,
		&destroy, cube);
	mlx_hook(cube->window_3d.ptr, ResizeRequest, ResizeRedirectMask,
		&w3d_resize, cube);
	if (IS_2D == 1)
	{
		mlx_hook(cube->window_2d.ptr, KeyPress, KeyPressMask,
			&key_press, cube);
		mlx_hook(cube->window_2d.ptr, KeyRelease, KeyReleaseMask,
			&key_release, cube);
		mlx_hook(cube->window_2d.ptr, DestroyNotify, StructureNotifyMask,
			&destroy, cube);
		mlx_hook(cube->window_2d.ptr, ResizeRequest, ResizeRedirectMask,
			&w2d_resize, cube);
	}
	mlx_loop_hook(cube->connection, update_movement, cube);
	mlx_loop(cube->connection);
}

int	main(int argc, char **argv)
{
	t_cube	cube;

	(void)argv;
	initialization(&cube);
	parse_argc(argc);
	define_map(&cube, argv[1]);
	define_windows(&cube);
	define_textures(&cube);
	if (IS_2D == 1)
		visualize_in_2d(&cube);
	draw_3d_scene(&cube);
	define_hook_loop(&cube);
	return (0);
}
