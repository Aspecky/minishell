/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:13:46 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/20 18:00:13 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_debug.h"
#include "execution.h"
#include "parsing.h"
#include <stdbool.h>

void parse(char *stream, char *const envp[], t_sllist *commands)
{
	t_sllist *tokens;

	if (!check_quotes_balance(stream))
		return;
	// TODO: Add $ expantion
	tokens = tokenize(stream);
	if (!tokens)
		return;
	// print_tokens(tokens);
	if (check_redirections(tokens))
	{
		remove_quotes(tokens);
		tokens_to_commands(commands, tokens);
		process_heredocs(commands);
	}
	sllist_free(tokens, token_free);
}
