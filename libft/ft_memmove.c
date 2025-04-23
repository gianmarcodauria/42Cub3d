/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:13:19 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/23 16:13:21 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*buff1;
	unsigned char	*buff2;

	buff1 = (unsigned char *)dest;
	buff2 = (unsigned char *)src;
	if (!dest && !src)
		return (dest);
	if (src < dest)
		while (n--)
			buff1[n] = buff2[n];
	else
		while (n--)
			*buff1++ = *buff2++;
	return (dest);
}
