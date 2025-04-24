/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:41:45 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/24 19:38:30 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



int	on_2d_resize(t_cube *cube)
{
	mlx_destroy_image(cube->connection, cube->map_image.ptr);
	visualize_in_2d(cube);
	return (0);
}

void	define_hook_loop(t_cube *cube)
{
	//mlx_hook(cube->window_3d.ptr, KeyPress, KeyPressMask, &mov_key_press, cube);
	//mlx_hook(cube->window_3d.ptr, KeyRelease, KeyReleaseMask, &mov_key_release, cube);
	//mlx_hook(cube->window_3d.ptr, DestroyNotify, StructureNotifyMask, &on_destroy, cube);
	//mlx_hook(cube->window_3d.ptr, ResizeRequest, ResizeRedirectMask, &on_3d_resize, cube);
	if (IS_2D == 1)
	{
		mlx_hook(cube->window_2d.ptr, KeyPress, KeyPressMask, &mov_key_press, cube);
		//mlx_hook(cube->window_2d.ptr, KeyRelease, KeyReleaseMask, &mov_key_release, cube);
		//mlx_hook(cube->window_2d.ptr, DestroyNotify, StructureNotifyMask, &on_destroy, cube);
		//mlx_hook(cube->window_2d.ptr, ResizeRequest, ResizeRedirectMask, &on_2d_resize, cube);
	}
	mlx_loop_hook(cube->connection, update_movement, cube);
	mlx_loop(cube->connection);
}

int main(int argc, char **argv)
{
	(void)argv;

	t_cube cube;


	initialization(&cube);
	parse_argc(argc);
	//se risultano corretti allora
	//costruiamo una mappa con le misure previste dove
	//eseguiremo anche il parsing:
	define_map(&cube, argv[1]);
	//settiamo le finestre
	define_windows(&cube);
	//assegniamo le texture
	//define_textures(&cube);
	//se siamo in 2d chiamiamo la mappa in 2d
	//altrimenti la disegniamo in 3d
	//*PER IL BONUS LA MAPPA 2D DEVE ESSERE SU QUELLA 3D*
	if (IS_2D == 1)
		visualize_in_2d(&cube);
	/*else
		visualize_in_3d(&cube);
*/
	//settiamo i tasti e definiamo il loop necessario
	//alla giocabilita
	define_hook_loop(&cube);
	return (0);
}
