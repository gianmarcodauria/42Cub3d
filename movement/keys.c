/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:33:04 by ccalabro          #+#    #+#             */
/*   Updated: 2025/04/28 17:34:19 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	key_release_position(int keycode, t_cube *cube)
{
	if (keycode == WW)
		cube->player.move.w = 0;
	if (keycode == SS)
		cube->player.move.s = 0;
	if (keycode == AA)
		cube->player.move.a = 0;
	if (keycode == DD)
		cube->player.move.d = 0;
}

static void	key_release_rotation(int keycode, t_cube *cube)
{
	if (keycode == RIGHT)
		cube->player.rotate_right = 0;
	if (keycode == LEFT)
		cube->player.rotate_left = 0;
}

int	key_release(int keycode, void *param)
{
	t_cube	*cube;

	cube = (t_cube *)param;
	key_release_position(keycode, cube);
	key_release_rotation(keycode, cube);
	return (0);
}

static void	key_press_position(int keycode, t_cube *cube)
{
	if (keycode == WW)
		cube->player.move.w = 1;
	if (keycode == SS)
		cube->player.move.s = 1;
	if (keycode == AA)
		cube->player.move.a = 1;
	if (keycode == DD)
		cube->player.move.d = 1;
}

static void	key_press_rotation(int keycode, t_cube *cube)
{
	if (keycode == RIGHT)
		cube->player.rotate_right = 1;
	if (keycode == LEFT)
		cube->player.rotate_left = 1;
}

int	key_press(int keycode, void *param)
{
	t_cube	*cube;

	cube = (t_cube *)param;
	if (keycode == ESC)
		destroy(cube);
	key_press_position(keycode, cube);
	key_press_rotation(keycode, cube);
	return (0);
}
