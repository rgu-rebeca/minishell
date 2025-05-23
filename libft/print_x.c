/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:22:27 by rgu               #+#    #+#             */
/*   Updated: 2025/04/09 15:22:27 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_hexa(unsigned int num)
{
	char	c;

	if (num / 16 > 0)
		ft_put_hexa(num / 16);
	if (num % 16 >= 10)
		c = 'a' + (num % 16) - 10;
	else
		c = num % 16 + '0';
	write (1, &c, 1);
}

int	print_x(unsigned int num)
{
	int				count;
	unsigned int	aux;

	count = 0;
	if (num == 0)
		count = 1;
	aux = num;
	while (aux > 0)
	{
		count++;
		aux = aux / 16;
	}
	ft_put_hexa(num);
	return (count);
}
