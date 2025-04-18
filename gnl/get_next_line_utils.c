/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:27:23 by lpennisi          #+#    #+#             */
/*   Updated: 2025/04/18 19:39:46 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	get_last(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len)
		len--;
	return (str[len]);
}
