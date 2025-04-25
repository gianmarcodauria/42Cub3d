/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:18:24 by lpennisi          #+#    #+#             */
/*   Updated: 2025/04/25 17:10:25 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	pitagora_theorem(t_point spawn_point, t_point second_point)
{
	double	result;
	double	dx;
	double	dy;

	dx = spawn_point.x - second_point.x;
	dy = spawn_point.y - second_point.y;
	result = sqrt(pow(dx, 2) + pow(dy, 2));
	return (result);
}

t_point	find_intersection(t_point p1, double p1_ang, t_point p2, double p2_ang)
{
	t_point	intersection;
	double	c1;
	double	c2;
	double	m1;
	double	m2;

	point_init(&intersection);
	if (cos(p1_ang) <= PI_FIX && cos(p1_ang) >= -PI_FIX)
		p1_ang += PI_FIX;
	if (cos(p2_ang) <= PI_FIX && cos(p2_ang) >= -PI_FIX)
		p2_ang += PI_FIX;
	m1 = tan(p1_ang);
	m2 = tan(p2_ang);
	c1 = p1.y - (m1 * p1.x);
	c2 = p2.y - (m2 * p2.x);
	intersection.x = (c2 - c1) / (m1 - m2);
	intersection.y = (m1 * intersection.x) + c1;
	return (intersection);
}

int	is_it_a_wall(t_point point_to_verify, char **map_grid)
{
	int	map_height;
	int	map_width;

	map_width = ft_strlen(map_grid[0]);
	map_height = ft_arrlen(map_grid);
	if (point_to_verify.x / 64 >= map_width || \
	point_to_verify.y / 64 >= map_height)
		return (FALSE);
	if (map_grid[(int)point_to_verify.y / 64][\
	(int)point_to_verify.x / 64] == '1')
		return (TRUE);
	return (FALSE);
}

int	is_it_inside_map_perimeter(t_point point, int width, int height)
{
	if (point.x >= 64 && \
	point.x < (width * 64 - 64) && \
	point.y >= 64 && \
	point.y < (height * 64) - 64)
		return (TRUE);
	return (FALSE);
}
