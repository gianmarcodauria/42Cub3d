/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:37:34 by ccalabro          #+#    #+#             */
/*   Updated: 2025/05/05 19:08:24 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_argc(int argc)
{
	if (argc != 2)
	{
		printf("ERROR: WRONG ARGC\n");
		exit(0);
	}
}

char	*parse_extention(char *path_of_map)
{
	char	**matrix_of_words;
	char	*extention;
	int		i;

	i = 0;
	extention = NULL;
	matrix_of_words = ft_split(path_of_map, '.');
	while (matrix_of_words[i])
	{
		if (extention)
			free(extention);
		extention = ft_strdup(matrix_of_words[i]);
		free(matrix_of_words[i]);
		i++;
	}
	free(matrix_of_words);
	return (extention);
}

void	exit_message(t_cube *cube, char *message)
{
	printf("%s\n", message);
	if (cube)
		destroy(cube);
	exit(0);
}

char	*read_texture_data(int fd)
{
	char	*line;
	char	*content_file;
	int		i;

	content_file = ft_safe_malloc(1);
	content_file[0] = '\0';
	i = 0;
	while (i < 6)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_blank_line(line))
		{
			free(line);
			continue ;
		}
		content_file = ft_strjoin_free(content_file, line, 3);
		i++;
	}
	return (content_file);
}

int	process_line(int fd, char **content_file, int *before_cont, int *blank_line)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (1);
	if (is_blank_line(line))
	{
		free(line);
		if (!*before_cont)
			*blank_line = 1;
		return (0);
	}
	if (*blank_line)
		return (free(line), 2);
	*before_cont = 0;
	*content_file = ft_strjoin_free(*content_file, line, 3);
	return (0);
}

char	*read_map_data(t_cube *cube, int fd)
{
	char	*content_file;
	int		before_cont;
	int		blank_line;
	int		status;

	content_file = ft_safe_malloc(1);
	content_file[0] = '\0';
	before_cont = 1;
	blank_line = 0;
	while (1)
	{
		status = process_line(fd, &content_file, &before_cont, &blank_line);
		if (status == 1)
			break ;
		else if (status == 2)
		{
			free(content_file);
			exit_message(cube, "invalid map\n");
		}
	}
	return (content_file);
}

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

// 5 maggio
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

// fine 5 maggio
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
//inserisci anche le altre del main
