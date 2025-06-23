/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:22:12 by rgu               #+#    #+#             */
/*   Updated: 2025/04/09 15:22:12 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_unsigned(unsigned int n)
{
	char	c;

	if (n / 10 > 0)
		ft_putnbr_unsigned(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

int	print_u(unsigned int num)
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
		aux = aux / 10;
	}
	ft_putnbr_unsigned(num);
	return (count);
}
