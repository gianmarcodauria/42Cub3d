/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_point_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:01:30 by lpennisi          #+#    #+#             */
/*   Updated: 2025/04/25 17:22:48 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	n_corner(int x, int y, t_cube *cube)
{
	if (cube->file_map.grid[y][x + 1] == '0' \
		&& cube->file_map.grid[y + 1][x] == '0')
		return (1);
	return (0);
}

int	north(int x, int y, t_cube *cube)
{
	if (cube->file_map.grid[y][x] == '1')
		return (1);
	return (0);
}

int	west(int x, int y, t_cube *cube)
{
	if (cube->file_map.grid[y][x] == '1')
		return (1);
	return (0);
}
