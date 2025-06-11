/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauizqui <rauizqui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:10:52 by rauizqui          #+#    #+#             */
/*   Updated: 2025/06/11 21:46:41 by rauizqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

void print_env(t_env *env_list)
{
    if (!env_list)
        return;

    printf("%s=%s\n", env_list->key, env_list->value);
    print_env(env_list->next);
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

	prev = NULL;
	curr = *env_list;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env_list = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}
void print_export_error(const char *arg)
{
    printf("export: `%s': not a valid identifier\n", arg);
}

void	print_unset_error(char *arg)
{
	if (!arg)
		return ;
	printf("unset: `%s`: not a valid identifier\n", arg);
}

static int	is_valid_identifier(const char *arg)
{
	int	i;
	
	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_unset(char **args, t_env **env_list)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]))
			unset_var(env_list, args[i]);
		else
			print_unset_error(args[i]);
		i++;
	}
	return (0);
}



static char	*get_key_from_arg(const char *arg)
{
	int		i;
	char	*key;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = ft_substr(arg, 0, i);
	return (key);
}

static char	*get_value_from_arg(const char *arg)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return (NULL);
	return (ft_strdup(equal + 1));
}

static void	handle_export_arg(char *arg, t_env **env_list)
{
	char	*key;
	char	*value;

	if (!is_valid_identifier(arg))
	{
		print_export_error(arg);
		return ;
	}
	key = get_key_from_arg(arg);
	value = get_value_from_arg(arg);
	export_var(env_list, key, value);
}
int builtin_export(char **args, t_env **env_list)
{
    int i;

    if (!args[1])
    {
        print_sorted_env(*env_list);
        return (0);
    }
    i = 1;
    while (args[i])
    {
        handle_export_arg(args[i], env_list);
        i++;
    }
    return (0);
}

int	exec_built_in(t_cmd *cmd, t_env **env_list)
{
	int		i;
	char	*key;
	char	*value;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (ft_strcmp(cmd->args[0], "export") == 0)
	{
		i = 1;
		while (cmd->args[i])
		{
			key = NULL;
			value = NULL;
			split_key_value(cmd->args[i], &key, &value);
			if (!key)
			{
				ft_putstr_fd("export: invalid identifier\n", 2);
				i++;
				continue ;
			}
			export_var(env_list, key, value);
			i++;
		}
	}
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
	{
		i = 1;
		while (cmd->args[i])
		{
			unset_var(env_list, cmd->args[i]);
			i++;
		}
	}
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		print_env(*env_list);
	return (0);
}

