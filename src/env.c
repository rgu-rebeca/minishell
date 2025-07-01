/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:58:29 by rgu               #+#    #+#             */
/*   Updated: 2025/07/02 00:44:15 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern int	g_last_status;

t_env	*new_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	env_add_back(t_env **lst, t_env *new_node)
{
	t_env	*temp;

	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	char	*equal_pos;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		equal_pos = ft_strchr(envp[i], '=');
		if (!equal_pos)
		{
			i++;
			continue ;
		}
		key = ft_substr(envp[i], 0, equal_pos - envp[i]);
		value = ft_strdup(equal_pos + 1);
		env_add_back(&env_list, new_env_node(key, value));
		i++;
	}
	return (env_list);
}

char	*get_env_value(t_env *env_list, const char *var)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, var) == 0)
			return (ft_strdup(env_list->value));
		env_list = env_list->next;
	}
	return (ft_strdup(""));
}
