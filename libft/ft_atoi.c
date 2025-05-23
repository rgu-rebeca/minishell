/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:48:10 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 15:48:13 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	b;
	int	sign;
	int	result;

	b = 0;
	sign = 1;
	while (str[b] == 32 || (str[b] >= 9 && str[b] <= 13))
		b ++;
	result = 0;
	if (str[b] == '-' || str[b] == '+')
	{
		if (str[b] == '-')
			sign = -1;
		b ++;
	}
	while (str[b] != '\0' && '0' <= str[b] && str[b] <= '9')
	{
		result = result * 10 + (str[b] - '0');
		b ++;
	}
	return (result * sign);
}

/*int main()
{
    int final_result;
    char *str1 = "    +a1+-12--++----4223eawea1rw";
    final_result = ft_atoi(str1);
    printf("%d\n", final_result);
    return(0);
}*/