/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:21:48 by rgu               #+#    #+#             */
/*   Updated: 2025/04/09 15:21:50 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf_aux(const char *format, va_list args)
{
	int	count;

	count = 0;
	if (*format == 'c')
		count += print_c(va_arg(args, int));
	else if (*format == 'd' || *format == 'i')
		count += print_d(va_arg(args, int));
	else if (*format == 'p')
		count += print_p(va_arg(args, void *));
	else if (*format == 's')
		count += print_s(va_arg(args, char *));
	else if (*format == 'u')
		count += print_u(va_arg(args, unsigned int));
	else if (*format == 'x')
		count += print_x(va_arg(args, unsigned int));
	else if (*format == 'X')
		count += print_x_upper(va_arg(args, unsigned int));
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += ft_printf_aux(format, args);
			if (*format == '%')
			{
				count ++;
				write (1, "%", 1);
			}
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (count);
}
