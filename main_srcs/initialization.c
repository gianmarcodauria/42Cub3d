/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:08:33 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/28 17:19:07 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialization(t_cube *cube)
{
	ft_memset(cube, 0, sizeof(t_cube));
	cube->player.fov.angle = FOV_ANGLE;
}

void	initialize_ray(t_ray *ray)
{
	ft_memset(ray, 0, sizeof(t_ray));
}

void	point_init(t_point *point_to_initialize)
{
	point_to_initialize->x = 0;
	point_to_initialize->y = 0;
}
