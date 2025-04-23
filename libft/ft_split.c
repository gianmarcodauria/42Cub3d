/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:13:54 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/23 17:19:51 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_words_num(const char *s, char c)
{
	size_t	n;

	n = 0;
	while (*s)
	{
		if (*s != c)
		{
			++n;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (n);
}

char	**ft_split(const char *s, char c)
{
	char	**matrix;
	size_t	i;
	size_t	len;

	if (!s)
		return (0);
	i = 0;
	matrix = malloc(sizeof(char *) * (get_words_num(s, c) + 1));
	if (!matrix)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				++s;
			matrix[i++] = ft_substr(s - len, 0, len);
		}
		else
			++s;
	}
	matrix[i] = 0;
	return (matrix);
}
