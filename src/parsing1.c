/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauizqui <rauizqui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:00:23 by rgu               #+#    #+#             */
/*   Updated: 2025/06/24 15:56:05 by rauizqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = temp;
	}
}

t_token	*create_new_token(char *line, int *i, t_token *head, t_env *env_list)
{
	char	*word;
	char	*temp;
	t_token	*new_token;
	int		quote_type;

	quote_type = 0;
	word = extract_word(line, i, &quote_type);
	if (!word)
		return (free_tokens(head), NULL);
	if (quote_type != 1)
	{
		temp = word;
		word = expand_env_vars(temp, env_list);
		if (!word)
			return (free(temp), free_tokens(head), NULL);
		if (temp != word)
			free(temp);
	}
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (free(word), free_tokens(head), NULL);
	new_token->type = get_token_type(word);
	new_token->value = word;
	new_token->next = NULL;
	return (new_token);
}

t_token	*tokenize(char *line, t_env *env_list)
{
	int		i;
	t_token	*new_token;
	t_token	*head;
	t_token	*last;

	i = 0;
	head = NULL;
	last = NULL;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		new_token = create_new_token(line, &i, head, env_list);
		if (!new_token)
			return (NULL);
		if (!head)
			head = new_token;
		else
			last->next = new_token;
		last = new_token;
	}
	return (head);
}
