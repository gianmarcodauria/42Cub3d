/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalabro <ccalabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:09:36 by ccalabro          #+#    #+#             */
/*   Updated: 2025/04/29 15:09:37 by ccalabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	angle_normalization(double *angle)
{
	while (*angle < 0)
		*angle = *angle + 2 * PI_G;
	while (*angle >= 2 * PI_G)
		*angle = *angle - 2 * PI_G;
}

int	get_cardinal_direction(double angle)
{
	int	cardinal_direction;

	angle_normalization(&angle);
	cardinal_direction = BLACK;
	if (fabs(angle - 0) < EPSILON || fabs(angle - 2 * PI_G) < EPSILON)
		cardinal_direction = E;
	else if (fabs(angle - PI_G) < EPSILON)
		cardinal_direction = W;
	else if (fabs(angle - PI_G / 2) < EPSILON)
		cardinal_direction = S;
	else if (fabs(angle - (3 * PI_G) / 2) < EPSILON)
		cardinal_direction = N;
	else if (angle > 0 && angle < PI_G / 2)
		cardinal_direction = SE;
	else if (angle > PI_G / 2 && angle < PI_G)
		cardinal_direction = SW;
	else if (angle > PI_G && angle < (3 * PI_G) / 2)
		cardinal_direction = NW;
	else if (angle > (3 * PI_G) / 2 && angle < 2 * PI_G)
		cardinal_direction = NE;
	return (cardinal_direction);
}
