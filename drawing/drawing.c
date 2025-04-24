#include "cub3d.h"

void	drawing_routine(t_cube *cube)
{
	if (IS_2D)
	{
		mlx_destroy_image(cube->connection, cube->map_image.ptr);
		visualize_in_2d(cube);
	}
	//mlx_destroy_image(cube->connection, cube->scene_3d.ptr);
	//draw_3d_scene(cube);
}
