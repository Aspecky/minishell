/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:13:46 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/29 18:07:39 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_debug.h"
#include "minishell.h"
#include "parsing.h"
#include "utils.h"
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

static bool	on_error(t_sllist *tokens, const char *s1, const char *s2)
{
	g_last_exit_status = EXIT_FAILURE;
	sllist_clear(tokens, token_free);
	if (s1 && s2)
		print_error(s1, s2);
	return (false);
}

bool	parse(char *stream, char *const envp[], t_sllist *commands)
{
	t_sllist	tokens;

	tokens = (t_sllist){0, 0, 0};
	if (!validate_quotes_balance(stream))
		return (on_error(&tokens, "syntax error", "unclosed quote"));
	if (!tokenize(stream, &tokens))
		return (on_error(&tokens, "tokenizer", strerror(errno)));
	if (tokens.size < 1)
		return (true);
	if (!expand_words(&tokens, envp))
		return (on_error(&tokens, "expantion", strerror(errno)));
	if (!validate_tokens(&tokens))
		return (on_error(&tokens, 0, 0));
	remove_quotes(&tokens);
	if (!tokens_to_commands(commands, &tokens))
		return (on_error(&tokens, "tokens_to_commands", strerror(errno)));
	if (!process_heredocs(commands, envp))
	{
		if (errno != EINTR)
			return (on_error(&tokens, "heredoc", strerror(errno)));
		else
			return (on_error(&tokens, 0, 0));
	}
	return (sllist_clear(&tokens, token_free), true);
}
