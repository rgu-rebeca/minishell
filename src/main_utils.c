/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauizqui <rauizqui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:21:05 by rauizqui          #+#    #+#             */
/*   Updated: 2025/06/23 21:18:20 by rauizqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static char	**ft_arrdup_loop(char **copy, char **arr, int size)
{
	int	j;

	j = 0;
	while (j < size)
	{
		copy[j] = ft_strdup(arr[j]);
		if (!copy[j])
		{
			while (j-- > 0)
				free(copy[j]);
			free(copy);
			return (NULL);
		}
		j++;
	}
	copy[size] = NULL;
	return (copy);
}

char	**ft_arrdup(char **arr)
{
	int		i;
	char	**copy;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	return (ft_arrdup_loop(copy, arr, i));
}

void	ft_arrfree(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	update_underscore(t_env **env, char *last_arg)
{
	t_env	*node;
	char	*value;

	if (last_arg == NULL)
		return ;
	value = ft_strdup(last_arg);
	if (value == NULL)
		return ;
	node = find_env_node(*env, "_");
	if (node != NULL)
	{
		free(node->value);
		node->value = value;
	}
	else
	{
		add_env_node(env, "_", value);
	}
}
