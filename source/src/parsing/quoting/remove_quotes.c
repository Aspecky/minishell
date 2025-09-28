/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 21:07:16 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/28 22:12:33 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	remove_str_quotes(char *str)
{
	size_t	i;
	size_t	j;
	char	quote;
	bool	was_quoted;

	was_quoted = false;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			was_quoted = true;
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				str[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
	return (was_quoted);
}

void	remove_quotes(t_sllist *tokens)
{
	t_slnode	*prev;
	t_slnode	*curr;
	t_slnode	*next;
	t_token		*token;

	prev = 0;
	curr = tokens->head;
	while (curr)
	{
		next = curr->next;
		token = curr->data;
		if (token->type == TOKEN_WORD)
		{
			if (token->value[0] == '\0')
			{
				sllist_pop(tokens, curr, prev);
				slnode_free(curr, token_free);
				curr = prev;
			}
			else
				token->was_quoted = remove_str_quotes(token->value);
		}
		prev = curr;
		curr = next;
	}
}
