/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:28:58 by ccalabro          #+#    #+#             */
/*   Updated: 2025/05/06 15:54:48 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_direction(double perpendicular_direction)
{
	if (perpendicular_direction >= -0.3925 && perpendicular_direction < 0.3925)
		return (S);
	if (perpendicular_direction >= 0.3925 && perpendicular_direction < 1.1775)
		return (SW);
	if (perpendicular_direction >= 1.1775 && perpendicular_direction < 1.9625)
		return (W);
	if (perpendicular_direction >= 1.9625 && perpendicular_direction < 2.7475)
		return (NW);
	if (perpendicular_direction >= 2.7475 && perpendicular_direction < 3.5325)
		return (N);
	if (perpendicular_direction >= 3.5325 && perpendicular_direction < 4.3175)
		return (NE);
	if ((perpendicular_direction >= 4.3175 && \
	perpendicular_direction <= 4.713) || \
	(perpendicular_direction >= -1.571 && \
	perpendicular_direction < -1.1775))
		return (E);
	if (perpendicular_direction >= -1.1775 && perpendicular_direction < -0.3925)
		return (SE);
	printf("error in get_direction with angle: %f\n", perpendicular_direction);
	return (0);
}

int	step_management(t_player *player, int foot_step_decrement)
{
	t_move	move;
	t_point	*position;
	int		direction;

	move = player->move;
	if ((move.w || move.s || move.a || move.d))
	{
		position = &player->position;
		direction = get_direction(player->perpendicular_direction);
		move_player_mains(direction, move, position, foot_step_decrement);
		return (TRUE);
	}
	return (FALSE);
}

int	moving(t_cube *cube)
{
	t_point	tmp;
	int		i;

	i = 0;
	tmp.x = cube->player.position.x;
	tmp.y = cube->player.position.y;
	while (i <= FOOT_JOB - 3)
	{
		if (step_management(&cube->player, i))
		{
			if (!is_collision(cube->player.position.x, cube->player.position.y,
					cube))
			{
				cube->player.tile = find_tile(cube->player.position);
				return (TRUE);
			}
		}
		cube->player.position.x = tmp.x;
		cube->player.position.y = tmp.y;
		i++;
	}
	return (FALSE);
}

int	set_rotation(t_cube *cube)
{
	int	has_rotated;

	has_rotated = 0;
	if (cube->player.rotate_right)
	{
		cube->player.direction += PEDEGREE;
		if (cube->player.direction > 2 * PI_G)
			cube->player.direction = cube->player.direction - (2 * PI_G);
		has_rotated = 1;
	}
	else if (cube->player.rotate_left)
	{
		cube->player.direction -= PEDEGREE;
		if (cube->player.direction < 0)
			cube->player.direction = 2 * PI_G + cube->player.direction;
		has_rotated = 1;
	}
	return (has_rotated);
}

// int	update_position(void *param)
// {
// 	t_cube	*cube;
// 	int		ret;

// 	cube = (t_cube *)param;
// 	ret = moving(cube);
// 	return (ret);
// }

// int	update_rotation(void *param)
// {
// 	t_cube	*cube;
// 	int		has_rotated;

// 	cube = (t_cube *)param;
// 	has_rotated = 0;
// 	has_rotated = set_rotation(cube);
// 	cube->player.perpendicular_direction = cube->player.direction - (PI_G / 2);
// 	cube->player.fov.half_left = cube->player.direction - (FOV_ANGLE / 2);
// 	cube->player.fov.half_right = cube->player.direction + (FOV_ANGLE / 2);
// 	return (has_rotated);
// }

// int	update_movement(void *param)
// {
// 	int	pos_updated;
// 	int	rot_updated;

// 	pos_updated = update_position(param);
// 	rot_updated = update_rotation(param);
// 	if (pos_updated || rot_updated)
// 		drawing_routine((t_cube *)param);
// 	return (0);
// }
