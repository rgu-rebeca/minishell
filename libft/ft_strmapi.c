/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:43:07 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:43:07 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*ptr;
	size_t	aux;

	aux = 0;
	len = ft_strlen (s);
	if (!s || !f)
		return (NULL);
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (s[aux])
	{
		ptr[aux] = f(aux, s[aux]);
		aux++;
	}
	ptr[aux] = '\0';
	return (ptr);
}

/*static char	to_lower_odd(unsigned int i, char s)
{
	if (i % 2 != 0)
	{
		if (s >= 'A' && s <= 'Z')
			s = s + 32;
	}
	return (s);
}
	
int main(void)
{
	char const *s = "HELLO";
	char    *result;

	result = ft_strmapi(s, to_lower_odd );
	printf("the result is: %s", result);
	return 0;
}*/