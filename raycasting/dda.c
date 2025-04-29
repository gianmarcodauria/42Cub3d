/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:09:17 by ccalabro          #+#    #+#             */
/*   Updated: 2025/04/29 15:09:18 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	enstabilish_orient(t_ray *ray, int last_increment)
{
	int	ray_direction;

	ray_direction = ray->cardinal_direction;
	if (last_increment == INCREMENT_X)
	{
		if (ray_direction == NW || ray_direction == SW || ray_direction == W)
			ray->orientation = E;
		else
			ray->orientation = W;
	}
	else
	{
		if (ray_direction == NW || ray_direction == NE || ray_direction == N)
			ray->orientation = S;
		else
			ray->orientation = N;
	}
}

static int	check_wall_collision(t_ray *ray, t_cube *c3d)
{
	if (is_it_passing_between_two_walls(ray, c3d->file_map.grid,
			ray->end_point))
		return (TRUE);
	if (is_it_a_wall(ray->end_point, c3d->file_map.grid))
		return (TRUE);
	return (FALSE);
}

t_ray	dda(t_point start_point, double alpha, t_cube *c3d)
{
	t_ray	ray;

	initialize_ray(&ray);
	ray.cardinal_direction = get_cardinal_direction(alpha);
	ray.spawn_point = start_point;
	while (is_it_inside_map_perimeter(ray.spawn_point, c3d->file_map.width,
			c3d->file_map.height))
	{
		ray.first_side_point = chose_side_point(ray.spawn_point,
				ray.cardinal_direction);
		ray.delta = calc_delta(ray.spawn_point, ray.first_side_point,
				ray.cardinal_direction);
		ray.path = calculate_path(ray.delta, alpha);
		ray.end_point = calculate_end_point(&ray, alpha, c3d);
		if (check_wall_collision(&ray, c3d))
			break ;
		ray.spawn_point = ray.end_point;
	}
	enstabilish_orient(&ray, c3d->player.ray.last_increment);
	return (ray);
}
