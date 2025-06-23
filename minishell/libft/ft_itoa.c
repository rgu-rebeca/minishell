/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:41:16 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:41:17 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_calculate_len(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len = len + 1;
	while (n % 10 != 0 || n / 10 != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*c;

	len = 0;
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	len = ft_calculate_len (n);
	c = (char *)malloc(sizeof(char) * (len + 1));
	if (!c)
		return (NULL);
	c[len] = '\0';
	if (n < 0)
	{
		c[0] = '-';
		n = -n;
	}
	while (--len >= 0)
	{
		if (c[len] == '-')
			break ;
		c[len] = (n % 10) + '0';
		n = n / 10;
	}
	return (c);
}

/*int	main(void)
{
	int	n = 12344;
	char	*result = ft_itoa(n);
	printf("the result is: %s \n", result);
}*/