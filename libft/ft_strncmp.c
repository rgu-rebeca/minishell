/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:43:12 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:43:12 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && ((unsigned char)s1[i]) && ((unsigned char)s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i == n || n == 0)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*int main(void)
{
	const char  *str1 = "Hello";
	const char  *str2 = "hello";
	int size = 2;
	int result = strncmp(str1, str2, size);
	if (result > 0)
		printf("the first str is bigger than the second");
	else if (result == 0)
		printf("the first str is the same as the second");
	else
		printf("the first str is smaller than the second");
		return 0;
}*/