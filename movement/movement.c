#include "cub3d.h"


void	free_raw_map(t_cube *cube)
{
	// if (cube->file_map.texture_data)
	// 	free(cube->file_map.texture_data);
	if (cube->file_map.map_data)
		free(cube->file_map.map_data);
	if (cube->file_map.grid)
		ft_free_matrix(cube->file_map.grid, -1);
	if (cube->map_lines)
		ft_free_matrix(cube->map_lines, -1);
}

int	on_destroy(t_cube *cube)
{
	free_raw_map(cube);
	// if (cube->win_3d.ptr)
	// 	mlx_destroy_window(cube->connection, cube->win_3d.ptr);
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

static void	mov_key_release_position(int keycode, t_cube *cube)
{
	if (keycode == WW)
		cube->player.move.w = 0;
	if (keycode == SS)
		cube->player.move.s = 0;
	if (keycode == AA)
		cube->player.move.a = 0;
	if (keycode == DD)
		cube->player.move.d = 0;
}

/*this function manages the release of rotaionn of player's alpha direction
which is where the player is looking at in a particular moment.
it is called by key_release which is the call-back function managed by mlx_hook
*/
static void	mov_key_release_rotation(int keycode, t_cube *cube)
{
	if (keycode == RIGHT)
		cube->player.rotate_alpha_right = 0;
	if (keycode == LEFT)
		cube->player.rotate_alpha_left = 0;
}

/*this function has to be this sign becouse it is called in mlx_hook*/
int	mov_key_release(int keycode, void *param)
{
	t_cube	*cube;

	cube = (t_cube *)param;
	mov_key_release_position(keycode, cube);
	mov_key_release_rotation(keycode, cube);
	return (0);
}

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

void	move_face_north_east(t_move move, t_point *position, int step_decr)
{
	if (move.w)
	{
		position->y -= (FOOT_JOB - step_decr);
		position->x += (FOOT_JOB - step_decr);
	}
	if (move.s)
	{
		position->y += (FOOT_JOB - step_decr);
		position->x -= (FOOT_JOB - step_decr);
	}
	if (move.a)
	{
		position->x -= (FOOT_JOB - step_decr);
		position->y -= (FOOT_JOB - step_decr);
	}
	if (move.d)
	{
		position->x += (FOOT_JOB - step_decr);
		position->y += (FOOT_JOB - step_decr);
	}
}

void	move_face_north_west(t_move move, t_point *position, int step_decr)
{
	if (move.w)
	{
		position->y -= (FOOT_JOB - step_decr);
		position->x -= (FOOT_JOB - step_decr);
	}
	if (move.s)
	{
		position->y += (FOOT_JOB - step_decr);
		position->x += (FOOT_JOB - step_decr);
	}
	if (move.a)
	{
		position->x -= (FOOT_JOB - step_decr);
		position->y += (FOOT_JOB - step_decr);
	}
	if (move.d)
	{
		position->x += (FOOT_JOB - step_decr);
		position->y -= (FOOT_JOB - step_decr);
	}
}

void	move_face_south_east(t_move move, t_point *position, int step_decr)
{
	if (move.w)
	{
		position->y += (FOOT_JOB - step_decr);
		position->x += (FOOT_JOB - step_decr);
	}
	if (move.s)
	{
		position->y -= (FOOT_JOB - step_decr);
		position->x -= (FOOT_JOB - step_decr);
	}
	if (move.a)
	{
		position->x += (FOOT_JOB - step_decr);
		position->y -= (FOOT_JOB - step_decr);
	}
	if (move.d)
	{
		position->x -= (FOOT_JOB - step_decr);
		position->y += (FOOT_JOB - step_decr);
	}
}

void	move_face_south_west(t_move move, t_point *position, int step_decr)
{
	if (move.w)
	{
		position->y += (FOOT_JOB - step_decr);
		position->x -= (FOOT_JOB - step_decr);
	}
	if (move.s)
	{
		position->y -= (FOOT_JOB - step_decr);
		position->x += (FOOT_JOB - step_decr);
	}
	if (move.a)
	{
		position->x += (FOOT_JOB - step_decr);
		position->y += (FOOT_JOB - step_decr);
	}
	if (move.d)
	{
		position->x -= (FOOT_JOB - step_decr);
		position->y -= (FOOT_JOB - step_decr);
	}
}

void	move_player_oblq(int direction, t_move move, \
t_point *position, int step_decr)
{
	if (direction == NE)
		move_face_north_east(move, position, step_decr);
	else if (direction == NW)
		move_face_north_west(move, position, step_decr);
	else if (direction == SE)
		move_face_south_east(move, position, step_decr);
	else if (direction == SW)
		move_face_south_west(move, position, step_decr);
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

void	move_face_north(t_move move, t_point *position, int step_decr)
{
	if (move.w)
		position->y -= (FOOT_JOB - step_decr);
	if (move.s)
		position->y += (FOOT_JOB - step_decr);
	if (move.a)
		position->x -= (FOOT_JOB - step_decr);
	if (move.d)
		position->x += (FOOT_JOB - step_decr);
}

void	move_face_south(t_move move, t_point *position, int step_decr)
{
	if (move.w)
		position->y += (FOOT_JOB - step_decr);
	if (move.s)
		position->y -= (FOOT_JOB - step_decr);
	if (move.a)
		position->x += (FOOT_JOB - step_decr);
	if (move.d)
		position->x -= (FOOT_JOB - step_decr);
}

void	move_face_east(t_move move, t_point *position, int step_decr)
{
	if (move.w)
		position->x += (FOOT_JOB - step_decr);
	if (move.s)
		position->x -= (FOOT_JOB - step_decr);
	if (move.a)
		position->y -= (FOOT_JOB - step_decr);
	if (move.d)
		position->y += (FOOT_JOB - step_decr);
}

void	move_face_west(t_move move, t_point *position, int step_decr)
{
	if (move.w)
		position->x -= (FOOT_JOB - step_decr);
	if (move.s)
		position->x += (FOOT_JOB - step_decr);
	if (move.a)
		position->y += (FOOT_JOB - step_decr);
	if (move.d)
		position->y -= (FOOT_JOB - step_decr);
}

void	move_player_mains(int direction, t_move move, \
t_point *position, int step_decr)
{
	if (direction == N)
		move_face_north(move, position, step_decr);
	else if (direction == S)
		move_face_south(move, position, step_decr);
	else if (direction == W)
		move_face_west(move, position, step_decr);
	else if (direction == E)
		move_face_east(move, position, step_decr);
	else
		move_player_oblq(direction, move, position, step_decr);
}

void	point_init(t_point *point_to_initialize)
{
	point_to_initialize->x = 0;
	point_to_initialize->y = 0;
}

int	is_it_inside_map_perimeter(t_point point, int map_width, int map_height)
{
	if (point.x >= 64 && point.x < (map_width* 64 - 64) && point.y >= 64 && point.y < (map_height * 64) - 64)
		return (TRUE);
	return (FALSE);
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

int	get_direction(double perpendicular_direction)
{
	if (perpendicular_direction >= -0.3925 && perpendicular_direction < 0.3925)
		return (S);
	if (perpendicular_direction >= 0.3925 && perpendicular_direction < 1.1775)
		return (SW);
	if (perpendicular_direction >= 1.1775 && perpendicular_direction < 1.9625)
		return (W);
	if (perpendicular_direction >= 1.9625 && perpendicular_direction < 2.7475)
		return (NW);
	if (perpendicular_direction >= 2.7475 && perpendicular_direction < 3.5325)
		return (N);
	if (perpendicular_direction >= 3.5325 && perpendicular_direction < 4.3175)
		return (NE);
	if ((perpendicular_direction >= 4.3175 && \
	perpendicular_direction <= 4.713) || \
	(perpendicular_direction >= -1.571 && \
	perpendicular_direction < -1.1775))
		return (E);
	if (perpendicular_direction >= -1.1775 && perpendicular_direction < -0.3925)
		return (SE);
	printf("error in get_direction with angle: %f\n", perpendicular_direction);
	return (0);
}

int	step_management(t_player *player, int foot_step_decrement)
{
	t_move	move;
	t_point	*position;
	int		direction;

	move = player->move;
	if ((move.w || move.s || move.a || move.d))
	{
		position = &player->position;
		direction = get_direction(player->perpendicular_direction);
		move_player_mains(direction, move, position, foot_step_decrement);
		return (TRUE);
	}
	return (FALSE);
}

/*this functions save the position of the player in a tmp variable.
Then works on this last variable.
It first update the coordinate of this point depending on step_management
function. Then it checks if the new point is a collision or not.
if everything was ok, the player position is update with the new valuse.
This function is also the occasion to update the tile where the player is in.
*/
int	moving(t_cube *cube)
{
	t_point	tmp;
	int		foot_step_decrement;

	foot_step_decrement = 0;
	tmp.x = cube->player.position.x;
	tmp.y = cube->player.position.y;
	while (foot_step_decrement <= FOOT_JOB - 3)
	{
		if (step_management(&cube->player, foot_step_decrement))
		{
			if (!is_collision(cube->player.position.x, \
			cube->player.position.y, cube))
			{
				cube->player.tile = find_tile(cube->player.position);
				return (TRUE);
			}
		}

		cube->player.position.x = tmp.x;
		cube->player.position.y = tmp.y;
		foot_step_decrement++;
	}
	return (FALSE);
}

/*
metto il check perchè altrimenti stampa in loop ogni volta con destory
e ristamp mappa
invece cosi lo fa solo se c'eè stato un cambiamento
This function colled from "update_player_movement" which in turn
is colled from mlx_loop_hook.
Well, it checks if one of the properties of player-position has been set to 1.
Remember that these are set to 1 from the  function key_press_player_position.
Remeber also that this  last (key_press_player_alpha_rotation) is called from
key_press which is called from
mlx_hook(cube.win.ptr, 2, 1L << 0, key_press, &cube), with second argument
2 which indicates the management of press.
If there is a collision simpli don't do anything. so don't update coordinates
of player.
*/
int	update_position(void *param)
{
	t_cube	*cube;

	cube = (t_cube *)param;
	return (moving(cube));
}

int	set_rotation(t_cube *cube)
{
	int	has_rotated;

	has_rotated = 0;
	if (cube->player.rotate_alpha_right)
	{
		cube->player.direction += PEDEGREE;
		if (cube->player.direction > 2 * PI_G)
			cube->player.direction = cube->player.direction - (2 * PI_G);
		has_rotated = 1;
	}
	else if (cube->player.rotate_alpha_left)
	{
		cube->player.direction -= PEDEGREE;
		if (cube->player.direction < 0)
			cube->player.direction = 2 * PI_G + cube->player.direction;
		has_rotated = 1;
	}
	return (has_rotated);
}

/*
metto il check perchè altrimenti stampa in loop ogni
volta con destory e ristamp mappa
invece cosi lo fa solo se c'eè stato un cambiamento
This function colled from "update_player_movement" whichi in turn
is colled from mlx_loop_hook.
Well, it checks if one of the properties of player-rotation
has been set to 1.
Remember that these are set to 1 from the  function
key_press_player_alpha_rotation.
Remeber also that this  last (key_press_player_alpha_rotation) is called from
key_press, which is called from
mlx_hook(cube.win.ptr, 2, 1L << 0, key_press, &cube),
with second argument 2 which indicates the management of press.
This function is useful even becouse it updates perpendicular_direction
of player and its left_half and right_half of the fov.
*/
int	update_alpha_rotation(void *param)
{
	t_cube	*cube;
	int		has_rotated;

	cube = (t_cube *)param;
	has_rotated = 0;
	has_rotated = set_rotation(cube);
	cube->player.perpendicular_direction = cube->player.direction - (PI_G / 2);
	cube->player.fov.half_left = cube->player.direction - (FOV_ANGLE / 2);
	cube->player.fov.half_right = cube->player.direction + (FOV_ANGLE / 2);
	return (has_rotated);
}

int	update_movement(void *param)
{
	int	pos_updated;
	int	rot_updated;

	pos_updated = update_position(param);
	rot_updated = update_alpha_rotation(param);
	if (pos_updated || rot_updated)
		drawing_routine((t_cube *)param);
	return (0);
}

/*this function manages the press of movement's player keycode
it is called by key_press() which is the call-back function managed by mlx_hook
Now, Questa funzioine è void ed ha due parametri perchè per costruzione fornisc
elementi di informazioni alla funzione di coll_back che ora abbiao citato.
La funzione di callback non può essere diversa da come è in termini di firma.
E quindi a cascata questa funzione anche è cosi.
deve avere un keycode. Questa funzione gestisceil keycode che le viene passato.
se il keycode è di un certo tipo allora setta il movimento del player.

*/
static void	mov_key_press_position(int keycode, t_cube *cube)
{
	if (keycode == WW)
		cube->player.move.w = 1;
	if (keycode == SS)
		cube->player.move.s = 1;
	if (keycode == AA)
		cube->player.move.a = 1;
	if (keycode == DD)
		cube->player.move.d = 1;
}

/*it is called by key_press which is the call-back function managed by mlx_hook
vedi spiegazione di keypress_playerposition*/
static void	mov_key_press_rotation(int keycode, t_cube *cube)
{
	if (keycode == RIGHT)
		cube->player.rotate_alpha_right = 1;
	if (keycode == LEFT)
		cube->player.rotate_alpha_left = 1;
}

/*this function has to be this sign becouse it is called in mlx_hook
in altri termini è obbligatorio avere un parametro int e uno void*.
Al parametro int è passato il keycode dalla funzione mlx_hook.
Quella funziona attualmente è impaostat acon un codice evento
(Che non è il keycode)
2. il codice evento 2 indiche che quella funzione è in ascolto sugli eventi di
pressione della tastiera.
Ecco quindi che restituirà il keycode(codice tel tasto della tastiera)
che è stato pigiato.
Ecco quindi che la palla passa alle funzioni che keypress ha internamente.
In pratica key_press riceve il keycode.
e successivamente il keycode è gestito da key_oress playerposiziont
 e keypressplayer direction
*/
int	mov_key_press(int keycode, void *param)
{
	t_cube	*cube;

	cube = (t_cube *)param;
	// if (keycode == ESC)
	// 	on_destroy(cube);
	mov_key_press_position(keycode, cube);
	mov_key_press_rotation(keycode, cube);
	return (0);
}
