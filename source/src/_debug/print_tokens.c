/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:00:00 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/15 21:32:06 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_debug.h"
#include "lexer.h"
#include <stdio.h>

static const char *token_type_to_string(t_token_type type)
{
	switch (type)
	{
		case TOKEN_WORD:
			return "WORD";
		case TOKEN_PIPE:
			return "PIPE";
		case TOKEN_REDIRECT_IN:
			return "REDIRECT_IN";
		case TOKEN_REDIRECT_OUT:
			return "REDIRECT_OUT";
		case TOKEN_REDIRECT_APPEND:
			return "REDIRECT_APPEND";
		case TOKEN_EOF:
			return "EOF";
		default:
			return "UNKNOWN";
	}
}

void print_tokens(const t_sllist *tokens)
{
	t_slnode *current;
	t_token *token;
	size_t index;

	if (!tokens)
	{
		printf("Tokens: NULL\n");
		return;
	}

	printf("Tokens (size: %zu):\n", tokens->size);

	if (tokens->size == 0 || !tokens->head)
	{
		printf("  No tokens\n");
		return;
	}

	index = 0;
	current = tokens->head;
	while (current)
	{
		token = (t_token *)current->data;
		
		if (!token)
		{
			printf("  [%zu] NULL token\n", index);
		}
		else
		{
			printf("  [%zu] Type: %-15s Value: ", index, token_type_to_string(token->type));
			if (token->value)
			{
				printf("\"%s\"", token->value);
			}
			else
			{
				printf("NULL");
			}
			printf("\n");
		}
		
		current = current->next;
		index++;
	}
}
