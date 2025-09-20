/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 21:07:16 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/20 18:00:13 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void remove_str_quotes(char *str)
{
	size_t i;
	size_t j;
	char quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i++; // Skip opening quote
			while (str[i] && str[i] != quote)
				str[j++] = str[i++];
			if (str[i] == quote)
				i++; // Skip closing quote
		} else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

void remove_quotes(t_sllist *tokens)
{
	t_slnode *node;
	t_token *token;

	node = tokens->head;
	while (node)
	{
		token = node->data;
		if (token->type == TOKEN_WORD)
			remove_str_quotes(token->value);
		node = node->next;
	}
}
