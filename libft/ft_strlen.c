/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:45:49 by lpennisi          #+#    #+#             */
/*   Updated: 2025/04/22 18:29:42 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

int	ft_arrlen(char **array)
{
	int	len;

	len = 0;
	if (!array)
		return (0);
	while (array[len])
		len++;
	return (len);
}

int	ft_arrlen_tillstr(char **array, const char *str)
{
	int	len;

	len = 0;
	if (!array)
		return (0);
	while (array[len] && ft_strcmp(array[len], str))
		len++;
	return (len);
}
