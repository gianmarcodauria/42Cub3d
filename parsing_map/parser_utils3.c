/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:02:21 by ccalabro          #+#    #+#             */
/*   Updated: 2025/05/06 17:03:13 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	checks(char **lines, t_map *file_map, int i, int j)
{
	if (!is_map_character(lines[i][j]))
		return (1);
	else if (is_player_character(lines[i][j]))
	{
		if (!file_map->player_orientation)
		{
			file_map->player_position = (t_point) \
			{j * 64 + 64 / 2, i * 64 + 64 / 2};
			file_map->player_orientation = get_orientation(lines[i][j]);
		}
		else
			return (1);
	}
	return (0);
}

int	check_map_characters(t_map *file_map, char **lines)
{
	int	i;
	int	j;

	i = -1;
	while (lines[++i])
	{
		j = -1;
		while (lines[i][++j])
		{
			if (checks(lines, file_map, i, j))
				return (1);
		}
	}
	if (!file_map->player_orientation)
		return (1);
	return (0);
}

int	check_texture_path(t_map *file_map, char *line)
{
	char	*path;
	char	*ptr;

	ptr = ft_strchr(line, ' ');
	if (!ptr)
		return (2);
	path = ft_strdup(ptr + 1);
	if (ft_strncmp(line, "NO ", 3) == 0)
		file_map->no_texture = path;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		file_map->so_texture = path;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		file_map->we_texture = path;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		file_map->ea_texture = path;
	else
		return (free(path), 2);
	if (access(path, F_OK) == -1)
		return (1);
	return (0);
}

int	are_information_set(t_map file_map)
{
	if (!file_map.no_texture || !file_map.so_texture || !file_map.we_texture \
	|| !file_map.ea_texture || !file_map.floor_color || !file_map.ceiling_color)
		return (0);
	return (1);
}

void	remove_consecutives_space(char **lines)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == ' ' && lines[i][j + 1] == ' ')
			{
				k = j;
				while (lines[i][k])
				{
					lines[i][k] = lines[i][k + 1];
					k++;
				}
				lines[i][k] = '\0';
			}
			j++;
		}
		i++;
	}
}
