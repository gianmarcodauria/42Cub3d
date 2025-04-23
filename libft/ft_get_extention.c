/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_extention.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:11:20 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/23 16:11:21 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"

char	*ft_get_extention(char *pathfile)
{
	char	**words;
	char	*ext;
	int		i;

	i = 0;
	ext = NULL;
	words = ft_split(pathfile, '.');
	while (words[i])
	{
		if (ext)
			free(ext);
		ext = ft_strdup(words[i]);
		free(words[i]);
		i++;
	}
	free(words);
	return (ext);
}
