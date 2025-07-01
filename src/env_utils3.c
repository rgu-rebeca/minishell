/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:57:04 by rauizqui          #+#    #+#             */
/*   Updated: 2025/07/01 23:24:23 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

void	print_env(t_env *env_list)
{
	while (env_list)
	{
		if (env_list->value)
			printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}

t_env	*find_env_node(t_env *env_list, const char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	add_env_node(t_env **env_list, char *key, char *value)
{
	t_env	*new_node;
	t_env	*temp;

	new_node = new_env_node(key, value);
	if (!new_node)
		return ;
	if (*env_list == NULL)
	{
		*env_list = new_node;
		return ;
	}
	temp = *env_list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
}

void	print_export_error(const char *arg)
{
	printf("export: `%s': not a valid identifier\n", arg);
}

void	print_unset_error(char *arg)
{
	if (!arg)
		return ;
	printf("unset: `%s`: not a valid identifier\n", arg);
}
