/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:42:37 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:42:37 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(char const *s, char c)
{
	int	in_word;
	int	count;

	in_word = 0;
	count = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*ft_word_group(char const *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *) malloc(sizeof(char) *(end - start + 1));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static void	ft_free_result(char **result, size_t word)
{
	size_t	i;

	i = 0;
	while (i < word)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

int	ft_split_aux(char const *s, char c, char **result, int j)
{
	size_t	h;
	int		i;

	h = 0;
	i = 0;
	while (s[j])
	{
		if (s[j] != c)
		{
			i = j;
			while (s[j] != c && s[j])
				j++;
			result[h] = ft_word_group(s, i, j);
			if (!result[h])
			{
				ft_free_result(result, h);
				return (0);
			}
			h++;
		}
		else
			j++;
	}
	result[h] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		j;
	char	**result;

	j = 0;
	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!result)
		return (NULL);
	if (!ft_split_aux(s, c, result, j))
		return (NULL);
	return (result);
}

/*int	main(void)
{
	char	*str1 = "HELLO world por fin !!";
	char	c = ' ';
	char	**result = ft_split(str1, c);
	int	i = 0;
	if (result)
	{
		while (result[i])
		{
			printf("%s\n", result[i]);
			free (result[i]);
			i++;
		}
		free (result);
	}
	else
		printf ("error");
}*/