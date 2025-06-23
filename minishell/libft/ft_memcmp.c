/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:42:02 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:42:02 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	size_t				i;
	const unsigned char	*p1;
	const unsigned char	*p2;

	i = 0;
	p1 = (const unsigned char *) ptr1;
	p2 = (const unsigned char *) ptr2;
	while (i < num)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	if (i == num || num == 0)
		return (0);
	return (p1[i] - p1[i]);
}

/*int main(void)
{
	const char str1[6] = "\0ello";
	const char str2[8] = "hello";
	int size = 2;
	int result = ft_memcmp(str1, str2, size);
	if (result > 0)
		printf("the first str is bigger than the second");
	else if (result == 0)
		printf("the first str is the same as the second");
	else
		printf("the first str is smaller than the second");
		return 0;
}*/