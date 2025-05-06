/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_closed_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:14:16 by ccalabro          #+#    #+#             */
/*   Updated: 2025/05/06 16:14:34 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_previous_row(t_cube *cube, char **map_lines, int prev_r_len,
			int i)
{
	int	j;
	int	row_length;

	row_length = ft_strlen(map_lines[i]);
	j = row_length;
	while (j < prev_r_len)
	{
		if (map_lines[i - 1][j] != '1')
			exit_message(cube, \
			"Error\nMap is not closed: gap in shorter row (previous row)");
		j++;
	}
}

void	check_next_row(t_cube *cube, char **map_lines, int next_r_len, int i)
{
	int	j;
	int	row_length;

	row_length = ft_strlen(map_lines[i]);
	j = row_length;
	while (j < next_r_len)
	{
		if (map_lines[i + 1][j] != '1')
			exit_message(cube, \
			"Error\nMap is not closed: gap in shorter row (next row)");
		j++;
	}
}
