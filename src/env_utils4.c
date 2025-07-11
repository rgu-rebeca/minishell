/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:46:04 by rauizqui          #+#    #+#             */
/*   Updated: 2025/07/11 03:07:30 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern int	g_last_status;

int	export_var(t_env **env_list, char *key, char *value)
{
	t_env	*node;

	node = find_env_node(*env_list, key);
	if (node)
	{
		free(node->value);
		if (value)
			node->value = ft_strdup(value);
		else
			node->value = ft_strdup("");
	}
	else
	{
		if (value)
			add_env_node(env_list, ft_strdup(key), ft_strdup(value));
		else
			add_env_node(env_list, ft_strdup(key), ft_strdup(""));
	}
	return (0);
}

int	unset_var(t_env **env_list, char *key)
{
	t_env	*prev;
	t_env	*curr;
	t_env	*to_delete;

	prev = NULL;
	curr = *env_list;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			to_delete = curr;
			if (prev)
				prev->next = curr->next;
			else
				*env_list = curr->next;
			curr = curr->next;
			free(to_delete->key);
			free(to_delete->value);
			free(to_delete);
			continue ;
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

static char	*join_until_closing_quote(char **args,
			int *i, char *merged, char quote)
{
	char	*temp;
	char	*temp2;
	int		found_quote;

	found_quote = 0;
	while (args[*i + 1])
	{
		temp = merged;
		merged = ft_strjoin(merged, " ");
		free(temp);
		temp2 = ft_strjoin(merged, args[*i + 1]);
		free(merged);
		merged = temp2;
		(*i)++;
		if (ft_strchr(args[*i], quote))
		{
			found_quote = 1;
			break ;
		}
	}
	if (!found_quote)
		return (ft_putendl_fd("export: quote is not closed", 2),
			free(merged), NULL);
	return (merged);
}

static char	*handle_quoted_export(char **args, int *i)
{
	char	*merged;
	char	quote;
	char	*equal;

	quote = 0;
	if (!ft_strchr(args[*i], '=') || !args[*i + 1])
		return (NULL);
	equal = ft_strchr(args[*i], '=');
	if (*(equal + 1) == '"' || *(equal + 1) == '\'')
		quote = *(equal + 1);
	if (!quote)
		return (NULL);
	merged = ft_strdup(args[*i]);
	return (join_until_closing_quote(args, i, merged, quote));
}

int	builtin_export(char **args, t_exec_data *data)
{
	int		i;
	char	*merged;

	if (!args[1])
	{
		print_sorted_env(data->env_list);
		g_last_status = 0;
		return (0);
	}
	i = 1;
	while (args[i])
	{
		merged = handle_quoted_export(args, &i);
		if (merged)
		{
			handle_export_arg(merged, &data->env_list);
			free(merged);
		}
		else
			handle_export_arg(args[i], &data->env_list);
		i++;
	}
	g_last_status = 0;
	data->dirty_envp = 1;
	return (0);
}
