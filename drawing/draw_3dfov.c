/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dfov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:40:58 by ccalabro          #+#    #+#             */
/*   Updated: 2025/05/06 15:30:10 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_oriented_texture_color(int orientation)
{
	if (orientation == N)
		return (RED);
	else if (orientation == S)
		return (GREEN);
	else if (orientation == W)
		return (PINK);
	else
		return (YELLOW);
}

int	get_orientation_id(int orientation)
{
	if (orientation == N)
		return (0);
	else if (orientation == S)
		return (1);
	else if (orientation == W)
		return (2);
	else
		return (3);
}

static void	set_pixels(int x_texture, t_cube *cube, t_ray ray)
{
	int		y_texture;
	int		color;
	double	max_iteration;
	double	y;
	double	y_min;

	y = cube->window_2d.height / 2 - \
	(cube->player.ray.height_wall_line / 2);
	y_min = y;
	max_iteration = y + cube->player.ray.height_wall_line;
	if (y < 0)
		y = 0;
	while (y < max_iteration && y < cube->window_2d.height)
	{
		y_texture = (cube->texture[get_orientation_id(ray.orientation)].\
		height * (y - y_min)) / \
		cube->player.ray.height_wall_line;
		if (SHOW_WITH_COLORS)
			color = get_oriented_texture_color(ray.orientation);
		else
			color = get_pixel(&cube->texture[\
				get_orientation_id(ray.orientation)], x_texture, y_texture);
		put_pixel(&cube->scene3d, cube->player.ray.x_wall_line, y, color);
		y++;
	}
}

void	draw_3d_vertical_line(t_cube *cube, t_ray ray,
		double saved_left_half_fov)
{
	int		x_text;
	t_point	end_point;

	end_point = ray.end_point;
	cube->player.ray.point_projection = find_intersection
		(cube->player.position, \
	cube->player.perpendicular_direction, end_point, cube->player.direction);
	cube->player.ray.x_wall_line = find_x_3d(cube->player.fov.half_left, \
	saved_left_half_fov, cube->window_3d.width);
	x_text = find_x_texture(end_point, cube->player.ray);
	cube->player.ray.len_projection = pitagora_theorem(end_point, \
	cube->player.ray.point_projection);
	cube->player.ray.height_wall_line = \
	calculate_3d_wall_height(cube->player);
	set_pixels(x_text, cube, ray);
}

void	draw_3d_fov(t_cube *cube)
{
	double	angle_variation;
	t_ray	ray;
	double	saved_left_half_fov;

	saved_left_half_fov = cube->player.fov.half_left;
	angle_variation = FOV_ANGLE / NUM_OF_RAYS;
	while (cube->player.fov.half_left < cube->player.fov.half_right)
	{
		ray = dda(cube->player.position, cube->player.fov.half_left, cube);
		if (IS_2D)
			bresenham(cube, ray.end_point.x, ray.end_point.y, PINK);
		draw_3d_vertical_line(cube, ray, saved_left_half_fov);
		cube->player.fov.half_left += angle_variation;
	}
}

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
