/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:00:04 by ccalabro          #+#    #+#             */
/*   Updated: 2025/05/06 17:00:24 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	remove_last_space(char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i])
	{
		j = ft_strlen(lines[i]) - 1;
		while (j >= 0 && lines[i][j] == ' ')
		{
			lines[i][j] = '\0';
			j--;
		}
		i++;
	}
}

void	remove_extra_space(char **lines)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (lines[++i])
	{
		j = 0;
		while (lines[i][j] == ' ')
			j++;
		if (j > 0)
		{
			k = 0;
			while (lines[i][j + k])
			{
				lines[i][k] = lines[i][j + k];
				k++;
			}
			lines[i][k] = '\0';
		}
	}
	remove_consecutives_space(lines);
	remove_last_space(lines);
}

int	are_all_digits(char **splitted)
{
	int	i;
	int	j;

	i = 0;
	while (splitted[i])
	{
		j = 0;
		while (splitted[i][j])
		{
			if (!ft_isdigit(splitted[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_color_format(t_map *file_map, char *line)
{
	char	**splitted;
	char	*color;

	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
	{
		color = ft_strchr(line, ' ') + 1;
		splitted = ft_split(color, ',');
		if (ft_arrlen(splitted) == 3)
		{
			if (!(ft_atoi(splitted[0]) < 0 || ft_atoi(splitted[0]) > 255 || \
			ft_atoi(splitted[1]) < 0 || ft_atoi(splitted[1]) > 255 || \
			ft_atoi(splitted[2]) < 0 || ft_atoi(splitted[2]) > 255) && \
			are_all_digits(splitted))
			{
				if (ft_strncmp(line, "F ", 2) == 0)
					file_map->floor_color = ft_strdup(color);
				else
					file_map->ceiling_color = ft_strdup(color);
				return (ft_free_matrix(splitted, -1), 0);
			}
		}
		return (ft_free_matrix(splitted, -1), 1);
	}
	return (2);
}

void	free_file_map(t_cube *cube)
{
	if (cube->file_map.texture_data)
		free(cube->file_map.texture_data);
	if (cube->file_map.map_data)
		free(cube->file_map.map_data);
	if (cube->file_map.grid)
		ft_free_matrix(cube->file_map.grid, -1);
	if (cube->file_map.no_texture)
		free(cube->file_map.no_texture);
	if (cube->file_map.so_texture)
		free(cube->file_map.so_texture);
	if (cube->file_map.we_texture)
		free(cube->file_map.we_texture);
	if (cube->file_map.ea_texture)
		free(cube->file_map.ea_texture);
	if (cube->file_map.floor_color)
		free(cube->file_map.floor_color);
	if (cube->file_map.ceiling_color)
		free(cube->file_map.ceiling_color);
	if (cube->map_lines)
		ft_free_matrix(cube->map_lines, -1);
}
