/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:56:33 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/28 16:04:02 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

static bool	do_expantion(t_token *token, char *const envp[],
		char *(*expand)(char *, char *const[]))
{
	char	*word;

	word = expand(token->value, envp);
	if (!word)
		return (false);
	free(token->value);
	token->value = word;
	return (true);
}

bool	expand_words(t_sllist *tokens, char *const envp[])
{
	t_slnode	*node;
	t_slnode	*prev;
	t_token		*token;

	node = tokens->head;
	prev = 0;
	while (node)
	{
		token = node->data;
		if (token->type == TOKEN_WORD && !(prev
				&& ((t_token *)(prev->data))->type == TOKEN_HEREDOC))
		{
			if (!do_expantion(token, envp, tilde_expantion)
				|| !do_expantion(token, envp, param_expantion))
				return (false);
		}
		prev = node;
		node = node->next;
	}
	return (true);
}
