/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:42:56 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:42:57 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	a;
	size_t	dst_len;

	a = 0;
	dst_len = 0;
	while (dst_len < dstsize && dst[dst_len])
		dst_len++;
	if (dstsize == dst_len)
		return (ft_strlen(src) + dst_len);
	while (src[a] && dstsize > dst_len + a + 1)
	{
		dst[dst_len + a] = src[a];
		a++;
	}
	dst[dst_len + a] = '\0';
	return (dst_len + ft_strlen(src));
}

/*int	main(void)
{
	const char	src[30] = "lorem ipsum dolor sit amet";
	char	dest[10] = "ab";
	int	dstsize = 10;
	int	expsize = ft_strlcat(dest, src, dstsize);
	printf("the expected size is: %d", expsize);
	printf("the new dest is: %s", dest);
}*/
