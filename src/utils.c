/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauizqui <rauizqui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:59:21 by rgu               #+#    #+#             */
/*   Updated: 2025/06/12 00:53:33 by rauizqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

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

int	ft_strcmp(const char *str1, const char *str2)
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
	return (a == '\f' || a == '\n' || a == '\r' || a == '\t' || a == '\v'
		|| a == ' ');
}

void split_key_value(const char *arg, char **key, char **value)
{
    int i = 0;

    *key = NULL;
    *value = NULL;

    while (arg[i] && arg[i] != '=')
        i++;

    if (arg[i] != '=')
    {
        *key = strdup(arg);
        *value = NULL;
        return;
    }

    *key = strndup(arg, i);
    if (!*key)
        return;
    *value = strdup(arg + i + 1);
}

void free_env_list(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}
