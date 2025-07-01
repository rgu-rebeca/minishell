/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:59:27 by rgu               #+#    #+#             */
/*   Updated: 2025/07/02 00:47:34 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

char	*join_path(char *dir, char *cmd)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, cmd);
	free(temp);
	return (path);
}

char	*get_path_env(t_env *env_list)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->key, "PATH", 4) == 0)
		{
			return (env_list->value);
			break ;
		}
		env_list = env_list->next;
	}
	return (NULL);
}

char	*get_command_path(char *cmd, t_env *env_list)
{
	int		i;
	char	**paths;
	char	*full_path;
	char	*path_env;

	i = 0;
	path_env = NULL;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = get_path_env(env_list);
	if (!path_env)
		return (NULL);
	i = 0;
	paths = ft_split(path_env, ':');
	while (paths[i])
	{
		full_path = join_path(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
			return (free_args(paths), full_path);
		free(full_path);
		i++;
	}
	free_args(paths);
	return (NULL);
}
