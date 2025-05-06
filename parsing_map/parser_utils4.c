/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:06:36 by ccalabro          #+#    #+#             */
/*   Updated: 2025/05/06 17:06:57 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	find_tile(t_point point)
{
	t_point	find_tile;

	find_tile.x = 0;
	find_tile.y = 0;
	find_tile.x = (int)(point.x / 64);
	find_tile.y = (int)(point.y / 64);
	return (find_tile);
}

void	define_player_orientation(t_cube *cube)
{
	if (cube->file_map.player_orientation == N)
		cube->player.direction = 3 * PI_G / 2;
	else if (cube->file_map.player_orientation == E)
		cube->player.direction = 0;
	else if (cube->file_map.player_orientation == S)
		cube->player.direction = PI_G / 2;
	else if (cube->file_map.player_orientation == W)
		cube->player.direction = PI_G;
	cube->player.perpendicular_direction = cube->player.direction - (PI_G / 2);
	cube->player.fov.half_left = cube->player.direction - (FOV_ANGLE / 2);
	cube->player.fov.half_right = cube->player.direction + (FOV_ANGLE / 2);
}

int	is_map_character(char c)
{
	if (c == '0' || c == '1' || c == 'N' \
	|| c == 'S' || c == 'E' || c == 'W' || c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_player_character(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	get_orientation(char c)
{
	if (c == 'N')
		return (N);
	else if (c == 'S')
		return (S);
	else if (c == 'E')
		return (E);
	else
		return (W);
}
