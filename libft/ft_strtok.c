/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:14:57 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/23 17:20:25 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *str, const char *accept)
{
	const char	*s;
	const char	*a;
	size_t		count;

	count = 0;
	s = str;
	while (*s)
	{
		a = accept;
		while (*a)
		{
			if (*s == *a)
				break ;
			++a;
		}
		if (*a == '\0')
			return (count);
		++count;
		++s;
	}
	return (count);
}

char	*ft_strpbrk(const char *str, const char *accept)
{
	const char	*s;
	const char	*a;

	s = str;
	while (*s)
	{
		a = accept;
		while (*a)
		{
			if (*s == *a)
				return ((char *)s);
			++a;
		}
		++s;
	}
	return (NULL);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*lasts;
	char		*start;
	char		*end;

	if (str == NULL)
		str = lasts;
	if (str == NULL)
		return (NULL);
	str += ft_strspn(str, delim);
	if (*str == '\0')
	{
		lasts = NULL;
		return (NULL);
	}
	start = str;
	end = ft_strpbrk(start, delim);
	if (end == NULL)
		lasts = NULL;
	else
	{
		*end = '\0';
		lasts = end + 1;
	}
	return (start);
}
