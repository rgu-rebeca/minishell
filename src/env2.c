/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:49:16 by rgu               #+#    #+#             */
/*   Updated: 2025/06/21 14:50:00 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern int	g_last_status;

void	expand_env_var_aux_1(char *status, int *i, char *result, int *n)
{
	status = ft_itoa(g_last_status);
	ft_strcpy(result + *n, status);
	*n += ft_strlen(status);
	free(status);
	*i += 2;
}

void	expand_env_var_aux_2(int *i, const char *str,
		t_env *env_list, char *result, int *n)
{
	int		j;
	char	var[256];
	char	*value;

	j = 0;
	(*i)++;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		var[j++] = str[(*i)++];
	var[j] = '\0';
	value = get_env_value(env_list, var);
	ft_strcpy(result + *n, value);
	*n += ft_strlen(value);
	free(value);
}

char	*expand_env_vars(const char *str, t_env *env_list)
{
	char	*result;
	int		i;
	int		n;
	char	*status;

	status = NULL;
	i = 0;
	n = 0;
	result = malloc(1024);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			expand_env_var_aux_1(status, &i, result, &n);
		else if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i
					+ 1] == '_'))
			expand_env_var_aux_2(&i, str, env_list, result, &n);
		else
			result[n++] = str[i++];
	}
	result[n] = '\0';
	return (result);
}
