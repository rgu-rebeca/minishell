/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:42:52 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:42:52 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new;
	char	*temp;

	s1_len = ft_strlen (s1);
	s2_len = ft_strlen (s2);
	new = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!new)
		return (NULL);
	temp = new;
	while (s1 && *s1)
	{
		*temp = *s1;
		temp++;
		s1++;
	}
	while (s2 && *s2)
	{
		*temp = *s2;
		temp++;
		s2++;
	}
	*temp = '\0';
	return (new);
}

/*int main(void)
{
	char const *s1 = "HELLO";
	char const *s2 = "HAHA";
	char    *new = ft_strjoin(s1, s2);
	if (new)
	{
		printf("the new string is %s", new);
		free (new);
	}
	else
		printf("error");
	return 0;
}*/