/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:42:10 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:42:11 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*a;
	unsigned char		*b;

	if (!dest && !src)
		return (NULL);
	a = (const unsigned char *)src;
	b = (unsigned char *) dest;
	if (b <= a)
	{
		i = 0;
		while (i < n)
		{
			b[i] = a[i];
			i++;
		}
	}
	else
	{
		while (n--)
			b[n] = a[n];
	}
	return (dest);
}

/*int main(void)
{
    char buffer[20] = "Hola, mundo!"; 
    printf("Antes: %s\n", buffer);
    
    char *result = ft_memmove(buffer + 2, buffer, 6);
	buffer[8] = '\0';
    printf("Después: %s\n", result);
    
    return 0;
}*/