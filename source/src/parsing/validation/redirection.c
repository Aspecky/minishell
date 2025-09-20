/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:37:36 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/20 18:00:13 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

bool check_redirections(t_sllist *tokens)
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
			{
				printf("syntax error: unexpected token near redirection\n");
				return (false);
			}
		}
		current = current->next;
	}
	return (true);
}
