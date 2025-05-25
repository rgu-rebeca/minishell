/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:58:29 by rgu               #+#    #+#             */
/*   Updated: 2025/05/24 15:58:29 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

char	*get_env_value(const char *var)
{
	char	*value;

	value = getenv(var);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*expand_env_vars(const char *str)
{
	char	*result;
	int		i;
	int		j;
	char	var[256];
	int		n;
	char	*value;
	int		k;

	result = malloc(1024);
	i = 0;
	j = 0;
	n = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			i++;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			var[n++] = str[i++];
		var[n] = '\0';
		value = get_env_value(var);
		while (value[k])
			result[j++] = value[k++];
		free(value);
		}
	else
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (ft_strdup(result));
}