/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:43:23 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:43:24 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_aux(size_t start, size_t end, char *result, char const *s1)
{
	int	i;

	i = 0;
	while (start <= end)
	{
		result[i] = s1[start];
		i++;
		start++;
	}
	result[i] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	if (s1[0] == '\0')
		return (ft_strdup(""));
	end = ft_strlen (s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (s1[end] && ft_strchr(set, s1[end]) && start < end)
		end--;
	if (end < start)
		return (ft_strdup(""));
	result = (char *)malloc(sizeof(char) *(end - start + 2));
	if (!result)
		return (NULL);
	ft_aux(start, end, result, s1);
	return (result);
}

/*int	main(void)
{
	char const	*test = "abcd";
	char const	*set = "";
	char *result = ft_strtrim(test, set);
	printf("%s\n", result);
}*/