/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:34:40 by ccalabro          #+#    #+#             */
/*   Updated: 2025/05/06 15:35:09 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_x_texture(t_point impact_point, t_ray ray)
{
	t_point	tile_point;
	int		x_texture;

	x_texture = 0;
	tile_point = find_tile(impact_point);
	if (ray.last_increment == INCREMENT_Y)
		x_texture = (impact_point.x - (tile_point.x * 64));
	else
		x_texture = (impact_point.y - (tile_point.y * 64));
	return (x_texture);
}

double	find_x_3d(double ray_angle, double fov_left_ray, double win_width)
{
	double	x_3d;
	double	angular_fov_percentage;
	double	win_width_angle_proportion;

	angular_fov_percentage = (ray_angle - fov_left_ray) / FOV_ANGLE;
	win_width_angle_proportion = angular_fov_percentage * win_width;
	x_3d = win_width_angle_proportion;
	return (x_3d);
}

double	calculate_3d_wall_height(t_player player)
{
	double	line_height;

	line_height = ((SCALE_FACTOR) / player.ray.len_projection);
	line_height *= (1 - line_height * 0.0001);
	return (line_height);
}
