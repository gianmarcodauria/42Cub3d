#include "cub3d.h"


void	inizialize_map_fm_file(t_map *file_map)
{
	file_map->width = 0;
	file_map->height = 0;
	file_map->texture_data = NULL;
	file_map->map_data = NULL;

	/*
	file_map->grid = NULL;
	file_map->player_orientation = 0;
	file_map->player_position = (t_point){0, 0};
	file_map->no_texture = 0;
	file_map->so_texture = 0;
	file_map->we_texture = 0;
	file_map->ea_texture = 0;
	file_map->f_color = 0;
	file_map->c_color = 0;
	*/
}
/*
void	initialize_player(t_player *player)
{
	player->direction = 0;
	player->perpendicular_direction = 0;
	player->position.x = 0;
	player->position.y = 0;
	player->move.w = 0;
	player->move.a = 0;
	player->move.s = 0;
	player->move.d = 0;
	player->rotate_alpha_right = 0;
	player->rotate_alpha_left = 0;
	player->ray.cardinal_direction = 0;
	player->ray.first_impact_point.x = 0;
	player->ray.first_impact_point.y = 0;
	player->ray.first_point.x = 0;
	player->ray.first_point.y = 0;
	player->ray.end_point.x = 0;
	player->ray.end_point.y = 0;
	player->fov.angle = FOV_ANGLE;
	player->fov.half_left = 0;
	player->fov.half_right = 0;
}
*/
/*
void	initialize_img(t_img *img)
{
	img->bits_per_pixel = 0;
	img->data_addr = NULL;
	img->endian = 0;
	img->img = NULL;
	img->img_dimension.w = 0;
	img->img_dimension.h = 0;
	img->size_line = 0;
}
*/
/*
void	initialize_ray(t_ray *ray)
{
	ray->cardinal_direction = 0;
	ray->first_side_point.x = 0;
	ray->first_side_point.y = 0;
	ray->first_impact_point.x = 0;
	ray->first_impact_point.y = 0;
	ray->delta.x = 0;
	ray->delta.y = 0;
	ray->path.x = 0;
	ray->path.y = 0;
	ray->first_point.x = 0;
	ray->first_point.y = 0;
	ray->end_point.x = 0;
	ray->end_point.y = 0;
	ray->projection.length = 0;
	ray->projection.point.x = 0;
	ray->projection.point.y = 0;
	ray->view3d.height_wall_line = 0;
	ray->view3d.x_wall_line = 0;
	ray->last_increment = 0;
}
*/


void	initialize_win(t_window *window)
{
	window->width = 0;
	window->height = 0;
	window->window_mlx= NULL;
}

void	initialization(t_cube *cube)
{
	//initialize_img(&cube->map_image);
	//initialize_img(&cube->texture[0]);
	//initialize_img(&cube->texture[1]);
	//initialize_img(&cube->texture[2]);
	//initialize_img(&cube->texture[3]);
	//initialize_player(&cube->player);
	initialize_win(&cube->window_2d);
	initialize_win(&cube->window_3d);
	inizialize_map_fm_file(&cube->file_map);
	cube->connection = NULL;
	cube->map_lines = NULL;
}
