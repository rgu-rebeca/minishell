/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:52:18 by rgu               #+#    #+#             */
/*   Updated: 2025/07/02 22:17:05 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

char	**env_list_to_array(t_env *env_list)
{
	char	**envp;
	int		count;
	t_env	*head;
	int		i;
	char	*temp;

	head = env_list;
	count = 0;
	i = 0;
	while (env_list && count++)
		env_list = env_list->next;
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	while (i < count)
	{
		temp = ft_strjoin(head->key, "=");
		envp[i] = ft_strjoin(temp, head->value);
		free(temp);
		i++;
		head = head->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	**update_envp(t_exec_data *data)
{
	int	i;

	if (data->dirty_envp)
	{
		if (data->envp)
		{
			i = 0;
			while (data->envp[i])
				free(data->envp[i++]);
			free(data->envp);
			data->envp = NULL;
		}
		data->envp = env_list_to_array(data->env_list);
		data->dirty_envp = 0;
	}
	return (data->envp);
}
