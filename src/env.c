/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauizqui <rauizqui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:58:29 by rgu               #+#    #+#             */
/*   Updated: 2025/06/13 11:14:25 by rauizqui         ###   ########.fr       */
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
		equal_pos = strchr(envp[i], '=');
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

char	*expand_env_vars(const char *str, t_env *env_list)
{
	char *result;
	int i = 0, n = 0;
	char var[256];
	char *value;

	result = malloc(1024);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			char *status = ft_itoa(g_last_status);
			ft_strcpy(result + n, status);
			n += ft_strlen(status);
			free(status);
			i += 2;
		}
		else if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i
				+ 1] == '_'))
		{
			int j = 0;
			i++;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				var[j++] = str[i++];
			var[j] = '\0';
			value = get_env_value(env_list, var);
			ft_strcpy(result + n, value);
			n += ft_strlen(value);
			free(value);
		}
		else
			result[n++] = str[i++];
	}
	result[n] = '\0';
	return (result);
}