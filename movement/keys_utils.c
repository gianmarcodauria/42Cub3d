/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:03:12 by ccalabro          #+#    #+#             */
/*   Updated: 2025/05/06 16:03:31 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
