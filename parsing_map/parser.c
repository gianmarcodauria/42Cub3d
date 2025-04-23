
#include "cub3d.h"

void	parse_argc(int argc)
{
	if (argc != 2)
	{
		printf("ERROR: WRONG ARGC\n");
		//implementa funzione per freeare
		//la struct
		//dato che nel main cio che fai per primo
		//é inizializzare la t_cube
		exit(0);
	}
}

//ok sono stati modificati variabili
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
// ok modificato
void	exit_message(t_cube *cube, char *message)
{
	printf("%s\n", message);
	if (cube)
		//on_destroy(cube);
	exit(0);
}

//AAA DA VEDERE
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
//AA DA VEDERE
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

//AAA DA VEDERE
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

int	checks(char **lines, t_map *raw_map, int i, int j)
{
	if (!is_map_character(lines[i][j]))
		return (1);
	else if (is_player_character(lines[i][j]))
	{
		if (!raw_map->player_orientation)
		{
			raw_map->player_position = (t_point) \
			{j * 64 + 64 / 2, i * 64 + 64 / 2};
			raw_map->player_orientation = get_orientation(lines[i][j]);
		}
		else
			return (1);
	}
	return (0);
}

int	check_map_characters(t_map *raw_map, char **lines)
{
	int	i;
	int	j;

	i = -1;
	while (lines[++i])
	{
		j = -1;
		while (lines[i][++j])
		{
			if (checks(lines, raw_map, i, j))
				return (1);
		}
	}
	if (!raw_map->player_orientation)
		return (1);
	return (0);
}

void	parse_and_check(t_cube *cube)
{
	t_map	*file_map;
	char	**map_lines;

	//check_texture_data(cube);
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
		exit_message(cube, "Error: an error occurred while reading the file.\n");
	cube->file_map.texture_data = read_texture_data(fd);
	cube->file_map.map_data = read_map_data(cube, fd);
	parse_and_check(cube);
}





//inserisci anche le altre del main

