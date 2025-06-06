/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:13:32 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/23 17:18:44 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	var_stamp(char ch, va_list varg)
{
	if (ch == 'c')
		return (ft_putchar(va_arg(varg, int)));
	else if (ch == 's')
		return (ft_putstr(va_arg(varg, char *)));
	else if (ch == 'p')
		return (ft_putptr(va_arg(varg, unsigned long long)));
	else if (ch == 'd' || ch == 'i')
		return (ft_putnbr(va_arg(varg, int)));
	else if (ch == 'u')
		return (ft_put_unsnbr(va_arg(varg, unsigned int)));
	else if (ch == 'x' || ch == 'X')
		return (ft_puthex(va_arg(varg, unsigned int), ch));
	else if (ch == '%')
		ft_putchar('%');
	else
	{
		ft_putchar('%');
		if ((ch > 'A' && ch < 'E') || (ch > 'H' && ch <= 'Z'))
			ft_putchar(ch);
	}
	return (1);
}

int	ft_printf(const char *s, ...)
{
	va_list	varg;
	int		counter;

	va_start(varg, s);
	counter = 0;
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			counter += var_stamp(*s, varg);
			s++;
			continue ;
		}
		write(1, s, 1);
		counter++;
		s++;
	}
	va_end(varg);
	return (counter);
}
