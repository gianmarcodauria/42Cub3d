/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:08:33 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/23 20:05:09 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	inizialize_map_fm_file(t_map *file_map)
{
	ft_memset(file_map, 0, sizeof(t_map));
}

void	player_initialization(t_player *player)
{
	ft_memset(player, 0, sizeof(t_player));
	player->fov.angle = FOV_ANGLE;

}

void	initialize_img(t_image *image)
{
	ft_memset(image, 0, sizeof(t_image));
}

void	initialize_ray(t_ray *ray)
{
	ft_memset(ray, 0, sizeof(t_ray));
}

void	initialize_win(t_window *window)
{
	ft_memset(window, 0, sizeof(t_window));
}

void	initialization(t_cube *cube)
{
	ft_memset(cube, 0, sizeof(t_cube));
}
