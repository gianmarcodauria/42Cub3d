/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:50:13 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/23 16:50:14 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"

void	ft_free_matrix(char **matrix, int len)
{
	int	i;

	i = 0;
	if (len == -1)
	{
		while (matrix[i] != NULL)
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
		return ;
	}
	while (i < len)
	{
		if (matrix[i] != NULL)
			free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	ft_free_matrix_3d(char ***matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		ft_free_matrix(matrix[i], -1);
		i++;
	}
	free(matrix);
}

void	*ft_safe_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
	{
		perror("Error allocating memory");
		exit(1);
	}
	return (ret);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*ret;

	if (ptr == NULL)
	{
		ret = ft_safe_malloc(size);
		return (ret);
	}
	if (size == 0)
		return (free(ptr), NULL);
	ret = ft_safe_malloc(size);
	ft_memcpy(ret, ptr, size);
	free(ptr);
	return (ret);
}
