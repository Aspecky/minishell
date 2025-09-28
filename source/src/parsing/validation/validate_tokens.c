/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:33:42 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/28 09:56:12 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

bool validate_tokens(t_sllist *tokens)
{
	t_slnode *current;
	t_token *token;

	current = tokens->head;
	while (current)
	{
		token = current->data;
		if (token->type == TOKEN_REDIRECT_IN ||
			token->type == TOKEN_REDIRECT_OUT ||
			token->type == TOKEN_REDIRECT_APPEND ||
			token->type == TOKEN_HEREDOC)
		{
			current = current->next;
			token = current->data;
			if (token->type != TOKEN_WORD)
				return (print_error("syntax error",
									"unexpected token near redirection"),
						false);
			if (token->type != TOKEN_HEREDOC && *(token->value) == '\0')
				return (print_error("syntax error", "ambiguous redirect"),
						false);
		} else if (token->type == TOKEN_PIPE)
		{
			current = current->next;
			token = current->data;
			if (token->type != TOKEN_WORD && token->type != TOKEN_HEREDOC)
				return (
					print_error("syntax error", "unexpected token near pipe"),
					false);
		}
		current = current->next;
	}
	return (true);
}
