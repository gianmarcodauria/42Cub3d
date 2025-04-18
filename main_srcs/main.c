/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:41:45 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/18 18:31:23 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int main(int argc, char **argv)
{
	(void)argv;
	//ci dichiariamo una struct principale
	//una t_cube
	t_cube cube;

	//procediamo ad inizializzare i campi
	//della struttura
	//initialize_cube(&cube);

	//controlliamo gli argc
	parse_argc(argc);

	//se risultano corretti allora
	//costruiamo una mappa con le misure previste dove
	//eseguiremo anche il parsing:
	printf("inizio main\n");
	define_map(&cube, argv[1]);


	//settiamo le finestre
	define_windows(&cube);

	//assegniamo le texture
	//define_textures(&cube);

	//se siamo in 2d chiamiamo la mappa in 2d
	//altrimenti la disegniamo in 3d
	//*PER IL BONUS LA MAPPA 2D DEVE ESSERE SU QUELLA 3D*
	/*if (IS_2D == 0)
		visualize_in_2d(&cube);
	else
		visualize_in_3d(&cube);
*/
	//settiamo i tasti e definiamo il loop necessario
	//alla giocabilita
	//define_hook_loop(&cube);

	return (0);
}
