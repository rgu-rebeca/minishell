/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauizqui <rauizqui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:16:54 by rauizqui          #+#    #+#             */
/*   Updated: 2025/06/11 21:20:23 by rauizqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

void	print_sorted_env(t_env *env)
{
	int count;
	t_env **arr;
	t_env *tmp;
	int i;
	int swapped;
	t_env *temp_node;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	if (count == 0)
		return ;
	arr = malloc(sizeof(t_env *) * count);
	if (!arr)
		return ;
	i = 0;
	tmp = env;
	while (tmp)
	{
		arr[i] = tmp;
		i++;
		tmp = tmp->next;
	}
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
	i = 0;
	while (i < count)
	{
		printf("declare -x %s=\"%s\"\n", arr[i]->key, arr[i]->value);
		i++;
	}
	free(arr);
}