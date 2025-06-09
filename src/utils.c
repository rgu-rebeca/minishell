/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauizqui <rauizqui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:59:21 by rgu               #+#    #+#             */
/*   Updated: 2025/06/09 20:07:37 by rauizqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_word(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (tokens->type == T_WORD)
			i++;
		tokens = tokens->next;
	}
	return (i);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return ((unsigned char)(str1[i]) - (unsigned char)(str2[i]));
		i++;
	}
	return ((unsigned char)(str1[i]) - (unsigned char)(str2[i]));
}

int	ft_isspace(int a)
{
	return (a == '\f' || a == '\n' || a == '\r'
		|| a == '\t' || a == '\v' || a == ' ');
}
