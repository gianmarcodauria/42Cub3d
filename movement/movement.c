#include "cub3d.h"


void	free_raw_map(t_cube *cube)
{
	if (cube->file_map.texture_data)
	 	free(cube->file_map.texture_data);
	if (cube->file_map.map_data)
		free(cube->file_map.map_data);
	if (cube->file_map.grid)
		ft_free_matrix(cube->file_map.grid, -1);
	if (cube->map_lines)
		ft_free_matrix(cube->map_lines, -1);
}

int	destroy(t_cube *cube)
{
	free_raw_map(cube);
	 if (cube->window_3d.ptr)
 		mlx_destroy_window(cube->connection, cube->window_3d.ptr);
	if (cube->window_2d.ptr)
		mlx_destroy_window(cube->connection, cube->window_2d.ptr);
	if (cube->connection)
	{
		if (cube->map_image.ptr)
			mlx_destroy_image(cube->connection, cube->map_image.ptr);
		mlx_destroy_display(cube->connection);
		free(cube->connection);
	}
	return (exit(0), 0);
}

t_point	get_circ_point(t_point player_next_position, double angle)
{
	t_point	circ_point;

	circ_point.x = 0;
	circ_point.y = 0;
	circ_point.x = player_next_position.x + RADIUS * cos(angle);
	circ_point.y = player_next_position.y + RADIUS * sin(angle);
	return (circ_point);
}

int	is_collision(double player_next_x, double player_next_y, t_cube *cube)
{
	t_point	player_next_position;
	t_point	circ_point;
	double	angle;
	int		loop;

	player_next_position.x = player_next_x;
	player_next_position.y = player_next_y;
	point_init(&circ_point);
	loop = 0;
	while (loop < CIRCUMFERENCE_CHECKS)
	{
		angle = 2 * PI_G * loop / CIRCUMFERENCE_CHECKS;
		circ_point = get_circ_point(player_next_position, angle);
		if (is_it_inside_map_perimeter(circ_point, cube->file_map.width, cube->file_map.height))
		{
			if (is_it_a_wall(circ_point, cube->file_map.grid))
				return (TRUE);
		}
		else
			return (TRUE);
		loop++;
	}
	return (FALSE);
}
