/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prntf_ptr_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:50:34 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/23 16:50:35 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ptr_len(unsigned long long n)
{
	int	c;

	c = 2;
	while (n != 0)
	{
		n = n / 16;
		c++;
	}
	return (c);
}

void	recursive_putptr(unsigned long long num)
{
	if (num >= 16)
	{
		recursive_putptr(num / 16);
		recursive_putptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar(num + '0');
		else
			ft_putchar(num - 10 + 'a');
	}
}

int	ft_putptr(unsigned long long num)
{
	write(1, "0x", 2);
	if (num == 0)
		return (write(1, "0", 1) + 2);
	else
		recursive_putptr(num);
	return (ptr_len(num));
}
