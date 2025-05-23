/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:42:59 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:43:00 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize > 0 && src[i] != '\0')
	{
		while ((i < dstsize - 1) && (src[i] != '\0'))
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

/*int	main(void)
{
	const char	src[20] = "lorem ipsum";
	char	dest[4] = "qwe";
	int	dstsize = 4;
	int	srcsize = ft_strlcpy(dest, src, dstsize);
	printf("the dest size is: %d\n", dstsize);
	printf("the src size is: %d\n", srcsize);
	printf("the new dest is: %s\n", dest);
}*/