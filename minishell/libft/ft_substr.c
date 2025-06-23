/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:43:27 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:43:27 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_aux(size_t len, unsigned int start, char const *s, char	*ptr)
{
	size_t	i;

	i = 0;
	while (i < len && (s[start + i]))
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen (s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	ptr = malloc (sizeof(char) * (len +1));
	if (ptr == NULL)
		return (NULL);
	ft_aux(len, start, s, ptr);
	return (ptr);
}

/*int main(void)
{
	char const  *str1 = "test123";
	unsigned int    start = 2;
	size_t  len = 3;
	char    *new_str = ft_substr(str1, start, len);
	if (new_str)
	{
		printf("the substring is: %s", new_str);
		free (new_str);
	}
	else
		printf("the substring genration failed");
}*/