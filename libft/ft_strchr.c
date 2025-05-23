/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:42:41 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:42:41 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if ((unsigned char)*str == (unsigned char) c)
			return ((char *) str);
		str++;
	}
	if ((unsigned char) c == '\0')
		return ((char *) str);
	return (NULL);
}

/*int main(void)
{
	const char str[20] = "hola, mundo.";
	int test = '\0';
	char    *result = ft_strchr(str, test);
	if (result)
		printf("the first apperance of the letter is:%s", result);
	else
		printf("%s", "not found");
	return (0);
}*/