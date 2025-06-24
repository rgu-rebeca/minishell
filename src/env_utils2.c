/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauizqui <rauizqui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:16:54 by rauizqui          #+#    #+#             */
/*   Updated: 2025/06/23 20:43:34 by rauizqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static int	count_env_nodes(t_env *env)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static void	fill_env_array(t_env **arr, t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		arr[i] = env;
		i++;
		env = env->next;
	}
}

static void	sort_env_array(t_env **arr, int count)
{
	int		i;
	int		swapped;
	t_env	*temp_node;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < count - 1)
		{
			if (ft_strcmp(arr[i]->key, arr[i + 1]->key) > 0)
			{
				temp_node = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp_node;
				swapped = 1;
			}
			i++;
		}
	}
}

static void	sort_and_print_env(t_env **arr, int count)
{
	int	i;

	sort_env_array(arr, count);
	i = 0;
	while (i < count)
	{
		printf("declare -x %s=\"%s\"\n", arr[i]->key, arr[i]->value);
		i++;
	}
}

void	print_sorted_env(t_env *env)
{
	int		count;
	t_env	**arr;

	count = count_env_nodes(env);
	if (count == 0)
		return ;
	arr = malloc(sizeof(t_env *) * count);
	if (!arr)
		return ;
	fill_env_array(arr, env);
	sort_and_print_env(arr, count);
	free(arr);
}
