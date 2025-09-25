/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:13:46 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/25 17:39:21 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_debug.h"
#include "parsing.h"
#include <stdbool.h>

void parse(char *stream, char *const envp[], t_sllist *commands)
{
	t_sllist *tokens;

	if (!check_quotes_balance(stream))
		return;
	tokens = tokenize(stream);
	if (!tokens)
		return;
	// print_tokens(tokens);
	// TODO: Validate what comes after pipe
	if (tokens->size > 1 && check_redirections(tokens))
	{
		expand_words(tokens, envp);
		// print_tokens(tokens);
		remove_quotes(tokens);
		tokens_to_commands(commands, tokens);
		// print_pipeline(commands);
		process_heredocs(commands, envp);
	}
	sllist_free(tokens, token_free);
}
