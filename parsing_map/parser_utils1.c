/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:48:23 by ccalabro          #+#    #+#             */
/*   Updated: 2025/05/06 16:48:46 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_destroy(t_cube *cube)
{
	free_file_map(cube);
	if (cube->window_3d.ptr)
		mlx_destroy_window(cube->connection, cube->window_3d.ptr);
	if (cube->window_2d.ptr)
		mlx_destroy_window(cube->connection, cube->window_2d.ptr);
	if (cube->connection)
	{
		if (cube->map_image.ptr)
			mlx_destroy_image(cube->connection, cube->map_image.ptr);
		if (cube->scene3d.ptr)
			mlx_destroy_image(cube->connection, cube->scene3d.ptr);
		if (cube->texture[0].ptr)
			mlx_destroy_image(cube->connection, cube->texture[0].ptr);
		if (cube->texture[1].ptr)
			mlx_destroy_image(cube->connection, cube->texture[1].ptr);
		if (cube->texture[2].ptr)
			mlx_destroy_image(cube->connection, cube->texture[2].ptr);
		if (cube->texture[3].ptr)
			mlx_destroy_image(cube->connection, cube->texture[3].ptr);
		mlx_destroy_display(cube->connection);
		free(cube->connection);
	}
	return (exit(0), 0);
}

void	error_exit(t_cube *cube, char *message)
{
	printf("%s\n", message);
	if (cube)
		on_destroy(cube);
	exit(0);
}

void	check_texture_data(t_cube *cube)
{
	t_map	*file_map;
	char	**lines;
	int		status;
	int		status2;
	int		i;

	file_map = &cube->file_map;
	lines = ft_split(file_map->texture_data, '\n');
	cube->map_lines = lines;
	i = -1;
	remove_extra_space(lines);
	while (lines[++i])
	{
		status = check_texture_path(file_map, lines[i]);
		if (status == 1)
			error_exit(cube, INVALID_TEXTURE_PATH);
		status2 = check_color_format(file_map, lines[i]);
		if (status2 == 1)
			error_exit(cube, INVALID_COLOR_FORMAT);
		if (status2 == 2 && status == 2)
			error_exit(cube, INVALID_MAP);
	}
	if (!are_information_set(*file_map))
		error_exit(cube, MISSING_INFORMATION);
}

void	parse_and_check(t_cube *cube)
{
	t_map	*file_map;
	char	**map_lines;

	check_texture_data(cube);
	file_map = &cube->file_map;
	map_lines = ft_split(file_map->map_data, '\n');
	cube->file_map.grid = map_lines;
	if (check_map_characters(file_map, map_lines))
		exit_message(cube, "INVALID_CHARACTER\n");
	cube->player.position = file_map->player_position;
	cube->player.tile = find_tile(cube->player.position);
	define_player_orientation(cube);
	check_map_closed(cube, map_lines);
}

void	define_map(t_cube *cube, char *path_of_map)
{
	int		fd;
	char	*extention;

	extention = parse_extention(path_of_map);
	if (extention)
	{
		if (ft_strcmp(extention, "cub"))
		{
			free(extention);
			exit_message(cube, "Error: Invalid map.\n");
		}
		free(extention);
	}
	if (access(path_of_map, F_OK) == -1)
		exit_message(cube, "Error: invalid path.\n");
	fd = open(path_of_map, O_RDONLY);
	if (fd == -1)
		exit_message(cube, "Error: a error occurred while reading the file.\n");
	cube->file_map.texture_data = read_texture_data(fd);
	cube->file_map.map_data = read_map_data(cube, fd);
	parse_and_check(cube);
}
