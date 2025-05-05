/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:50:10 by ccalabro          #+#    #+#             */
/*   Updated: 2025/05/05 19:04:04 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	define_textures(t_cube *cube)
{
	cube->texture[0].ptr = mlx_xpm_file_to_image(cube->connection, \
	cube->file_map.no_texture, &cube->texture[0].width, \
	&cube->texture[0].height);
	cube->texture[0].data_addr = mlx_get_data_addr(cube->texture[0].ptr, \
	&cube->texture[0].bits_x_pixel, &cube->texture[0].size_line, \
	&cube->texture[0].endian);
	cube->texture[1].ptr = mlx_xpm_file_to_image(cube->connection, \
	cube->file_map.so_texture, &cube->texture[1].width, \
	&cube->texture[1].height);
	cube->texture[1].data_addr = mlx_get_data_addr(cube->texture[1].ptr, \
	&cube->texture[1].bits_x_pixel, &cube->texture[1].size_line, \
	&cube->texture[1].endian);
	cube->texture[2].ptr = mlx_xpm_file_to_image(cube->connection, \
	cube->file_map.we_texture, &cube->texture[2].width, \
	&cube->texture[2].height);
	cube->texture[2].data_addr = mlx_get_data_addr(cube->texture[2].ptr, \
	&cube->texture[2].bits_x_pixel, &cube->texture[2].size_line, \
	&cube->texture[2].endian);
	cube->texture[3].ptr = mlx_xpm_file_to_image(cube->connection, \
	cube->file_map.ea_texture, &cube->texture[3].width, \
	&cube->texture[3].height);
	cube->texture[3].data_addr = mlx_get_data_addr(cube->texture[3].ptr, \
	&cube->texture[3].bits_x_pixel, &cube->texture[3].size_line, \
	&cube->texture[3].endian);
}
