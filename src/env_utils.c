/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:10:52 by rauizqui          #+#    #+#             */
/*   Updated: 2025/07/11 03:06:03 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern int	g_last_status;

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

static void	split_key_value(const char *arg, char **key, char **value)
{
	char	*equal;
	char	*tail;

	if (!arg || !key || !value)
		return ;
	*key = NULL;
	*value = NULL;
	equal = ft_strchr(arg, '=');
	if (equal)
	{
		*key = ft_substr(arg, 0, equal - arg);
		equal++;
		if (*(equal) == '"' || (*(equal)) == '\'')
			equal++;
		tail = equal;
		while (*tail)
			tail++;
		if (*(tail - 1) == '"' || *(tail - 1) == '\'')
			tail--;
		*value = ft_substr(equal, 0, tail - equal);
	}
	else
		*key = ft_strdup(arg);
}

void	handle_export_arg(char *arg, t_env **env_list)
{
	char	*key;
	char	*value;

	split_key_value(arg, &key, &value);
	if (!is_valid_identifier(key))
	{
		print_export_error(key);
		g_last_status = 1;
		return ;
	}
	export_var(env_list, key, value);
	free(key);
	free(value);
}

int	builtin_unset(char **args, t_exec_data *data)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]))
			unset_var(&data->env_list, args[i]);
		else
		{
			print_unset_error(args[i]);
			g_last_status = 1;
		}
		i++;
	}
	g_last_status = 0;
	data->dirty_envp = 1;
	return (0);
}
