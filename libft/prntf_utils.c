/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prntf_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:50:59 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/23 16:51:00 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	if (!s)
		return (0);
	write(1, s, ft_strlen(s));
	return (ft_strlen(s));
}
