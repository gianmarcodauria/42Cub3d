/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:08:33 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/24 19:32:28 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialization(t_cube *cube)
{
	ft_memset(cube, 0, sizeof(t_cube));
	cube->player.fov.angle = FOV_ANGLE;
}
