/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:21:59 by rgu               #+#    #+#             */
/*   Updated: 2025/04/09 15:22:00 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	print_d(int num)
{
	int	count;
	int	aux;

	count = 0;
	aux = num;
	if (num == INT_MIN)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	else if (aux <= 0)
	{
		aux = -aux;
		count++;
	}
	while (aux > 0)
	{
		count++;
		aux = aux / 10;
	}
	ft_putnbr_fd(num, 1);
	return (count);
}
