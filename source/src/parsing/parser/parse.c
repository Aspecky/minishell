/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:13:46 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/20 17:02:37 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_debug.h"
#include "execution.h"
#include "lexer.h"
#include "parser.h"
#include "quoting.h"
#include "validation.h"
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
	remove_quotes(tokens);
	// print_tokens(tokens);
	if (check_redirections(tokens))
	{
		tokens_to_commands(commands, tokens);
		process_heredocs(commands);
	}
	sllist_free(tokens, token_free);
}
