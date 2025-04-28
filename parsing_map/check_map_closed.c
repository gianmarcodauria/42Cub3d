/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:40:19 by ccalabro          #+#    #+#             */
/*   Updated: 2025/04/28 17:40:47 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_previous_row(t_cube *cube, char **map_lines, int prev_r_len,
			int i)
{
	int	j;
	int	row_length;

	row_length = strlen(map_lines[i]);
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

	row_length = strlen(map_lines[i]);
	j = row_length;
	while (j < next_r_len)
	{
		if (map_lines[i + 1][j] != '1')
			exit_message(cube, \
			"Error\nMap is not closed: gap in shorter row (next row)");
		j++;
	}
}

void	check_shorter_rows(t_cube *cube, char **map_lines, int height)
{
	int	i;
	int	row_length;
	int	prev_row_length;
	int	next_row_length;

	i = 1;
	while (i < height)
	{
		row_length = strlen(map_lines[i]);
		prev_row_length = strlen(map_lines[i - 1]);
		check_previous_row(cube, map_lines, prev_row_length, i);
		if (i >= height - 1)
			break ;
		next_row_length = strlen(map_lines[i + 1]);
		if (row_length < next_row_length)
			check_next_row(cube, map_lines, next_row_length, i);
		i++;
	}
}

void	check_first_last_row(t_cube *cube, char **map_lines, int height)
{
	int	j;

	j = 0;
	while (map_lines[0][j])
	{
		if (map_lines[0][j] != '1' && map_lines[0][j] != ' ' \
		&& map_lines[0][j] != '\t')
			exit_message(cube, "Error\nMap is not closed: first row\n");
		j++;
	}
	j = 0;
	while (map_lines[height - 1][j])
	{
		if (map_lines[height - 1][j] != '1' && map_lines[height - 1][j] \
		!= ' ' && map_lines[height - 1][j] != '\t')
			exit_message(cube, "Error\nMap is not closed: last row\n");
		j++;
	}
}

void	check_space(t_cube *cube, char **map_lines, int i, int height)
{
	int	j;
	int	row_length;

	j = 1;
	row_length = ft_strlen(map_lines[i]);
	while (j < row_length - 1)
	{
		if (map_lines[i][j] == ' ')
		{
			if ((i > 0 && map_lines[i - 1][j] == '0') ||
				(i < height - 1 && map_lines[i + 1][j] == '0') ||
				(j > 0 && map_lines[i][j - 1] == '0') ||
				(j < row_length - 1 && map_lines[i][j + 1] == '0'))
				exit_message(cube, \
				"Error\nMap is not closed: space inside row adjacent to '0'\n");
		}
		j++;
	}
}

void	check_first_last_column(t_cube *cube, char **map_lines, int height)
{
	int	i;
	int	row_length;

	i = 0;
	while (i < height)
	{
		row_length = ft_strlen(map_lines[i]);
		if (cube->file_map.width < row_length)
			cube->file_map.width = row_length;
		if (map_lines[i][0] != '1' && map_lines[i][0] != ' ' \
		&& map_lines[i][0] != '\t')
			exit_message(cube, "Error\nMap is not closed: first column\n");
		if (map_lines[i][row_length - 1] != '1' && map_lines[i] \
		[row_length - 1] != ' ' && map_lines[i][row_length - 1] != '\t')
			exit_message(cube, "Error\nMap is not closed: last column\n");
		check_space(cube, map_lines, i, height);
		i++;
	}
}

void	check_map_closed(t_cube *cube, char **map_lines)
{
	int	height;

	height = ft_arrlen(map_lines);
	cube->file_map.height = height;
	check_first_last_row(cube, map_lines, height);
	check_first_last_column(cube, map_lines, height);
	check_shorter_rows(cube, map_lines, height);
}
