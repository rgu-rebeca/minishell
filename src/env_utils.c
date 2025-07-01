/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:10:52 by rauizqui          #+#    #+#             */
/*   Updated: 2025/07/01 23:32:41 by rgu              ###   ########.fr       */
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
	size_t	len;

	if (!arg || !key || !value)
		return ;
	*key = NULL;
	*value = NULL;
	equal = ft_strchr(arg, '=');
	if (equal)
	{
		len = equal - arg;
		*key = ft_substr(arg, 0, len);
		*value = ft_strdup(equal + 1);
	}
	else
		*key = ft_strdup(arg);
}

static void	handle_export_arg(char *arg, t_env **env_list)
{
	char	*key;
	char	*value;

	if (!is_valid_identifier(arg))
	{
		print_export_error(arg);
		g_last_status = 1;
		return ;
	}
	split_key_value(arg, &key, &value);
	export_var(env_list, key, value);
	free(key);
	free(value);
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
		{
			print_unset_error(args[i]);
			g_last_status = 1;
		}
		i++;
	}
	g_last_status = 0;
	return (0);
}

int	builtin_export(char **args, t_env **env_list)
{
	int	i;

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
	g_last_status = 0;
	return (0);
}
