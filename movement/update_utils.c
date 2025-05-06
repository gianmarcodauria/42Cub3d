/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:52:57 by ccalabro          #+#    #+#             */
/*   Updated: 2025/05/06 15:53:45 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update_position(void *param)
{
	t_cube	*cube;
	int		ret;

	cube = (t_cube *)param;
	ret = moving(cube);
	return (ret);
}

int	update_rotation(void *param)
{
	t_cube	*cube;
	int		has_rotated;

	cube = (t_cube *)param;
	has_rotated = 0;
	has_rotated = set_rotation(cube);
	cube->player.perpendicular_direction = cube->player.direction - (PI_G / 2);
	cube->player.fov.half_left = cube->player.direction - (FOV_ANGLE / 2);
	cube->player.fov.half_right = cube->player.direction + (FOV_ANGLE / 2);
	return (has_rotated);
}

int	update_movement(void *param)
{
	int	pos_updated;
	int	rot_updated;

	pos_updated = update_position(param);
	rot_updated = update_rotation(param);
	if (pos_updated || rot_updated)
		drawing_routine((t_cube *)param);
	return (0);
}
