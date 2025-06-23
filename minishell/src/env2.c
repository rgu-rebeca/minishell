/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauizqui <rauizqui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:49:16 by rgu               #+#    #+#             */
/*   Updated: 2025/06/23 22:02:44 by rauizqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern int	g_last_status;

void	expand_env_var_aux_1(t_expand_aux *aux)
{
	char	*status;

	status = ft_itoa(g_last_status);
	ft_strcpy(aux->result + aux->n, status);
	aux->n += ft_strlen(status);
	free(status);
	aux->i += 2;
}

void	expand_env_var_aux_2(t_expand_aux *aux)
{
	int		j;
	char	var[256];
	char	*value;

	j = 0;
	aux->i++;
	while (aux->str[aux->i] && (ft_isalnum(aux->str[aux->i])
			|| aux->str[aux->i] == '_'))
		var[j++] = aux->str[aux->i++];
	var[j] = '\0';
	value = get_env_value(aux->env_list, var);
	ft_strcpy(aux->result + aux->n, value);
	aux->n += ft_strlen(value);
	free(value);
}

char	*expand_env_vars(const char *str, t_env *env_list)
{
	char			*result;
	t_expand_aux	aux;

	aux.i = 0;
	aux.n = 0;
	aux.str = str;
	aux.env_list = env_list;
	result = malloc(1024);
	if (!result)
		return (NULL);
	aux.result = result;
	while (str[aux.i])
	{
		if (str[aux.i] == '$' && str[aux.i + 1] == '?')
			expand_env_var_aux_1(&aux);
		else if (str[aux.i] == '$' && str[aux.i + 1] && (ft_isalnum(str[aux.i
						+ 1]) || str[aux.i + 1] == '_'))
			expand_env_var_aux_2(&aux);
		else
			result[aux.n++] = str[aux.i++];
	}
	result[aux.n] = '\0';
	return (result);
}
