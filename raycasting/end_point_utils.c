/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_point_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:09:57 by ccalabro          #+#    #+#             */
/*   Updated: 2025/04/29 15:09:58 by ccalabro         ###   ########.fr       */
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
