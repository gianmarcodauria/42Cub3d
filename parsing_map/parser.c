/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:37:34 by ccalabro          #+#    #+#             */
/*   Updated: 2025/05/06 17:15:08 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
