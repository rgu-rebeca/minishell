/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:43:15 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:43:16 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *momstr, const char *babystr, size_t len)
{
	size_t	n;
	size_t	a;

	n = 0;
	if (babystr[0] == '\0')
		return ((char *)momstr);
	while (momstr[n] != '\0' && n < len)
	{
		a = 0;
		while (momstr[n + a] == babystr[a] && (n + a) < len)
		{
			if (babystr[a + 1] == '\0')
				return ((char *)(&momstr[n]));
			a++;
		}
		n++;
	}
	return (NULL);
}

/*int	main(void)
{
	const char *mstr = "hola,mundo.";
	const char	*babystr= ",mundo";
	size_t len = 10;
	char *result = ft_strnstr(mstr, babystr,len);
	printf("%s", result);
}*/
