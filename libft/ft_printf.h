/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:22:42 by rgu               #+#    #+#             */
/*   Updated: 2025/04/09 15:22:43 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <limits.h>

int	ft_printf(const char *format, ...);
int	ft_printf(const char *format, ...);
int	print_c(int c);
int	print_d(int num);
int	print_p(void *ptr);
int	print_s(char *str);
int	print_u(unsigned int num);
int	print_x(unsigned int num);
int	print_x_upper(unsigned int num);

#endif 