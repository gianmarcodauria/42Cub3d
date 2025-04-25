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
