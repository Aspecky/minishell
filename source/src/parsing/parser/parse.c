/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:13:46 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/19 02:37:57 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_debug.h"
#include "lexer.h"
#include "parser.h"
#include "validation.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void parse(t_sllist *commands, char *stream)
{
	t_sllist *tokens;

	if (!check_quotes_balance(stream))
		return ;
	// TODO: Add $ expantion
	tokens = tokenize(stream);
	if (!tokens)
		return ;
	// print_tokens(tokens);
	if (!check_redirections(tokens))
		(sllist_free(tokens, token_free));
	tokens_to_commands(commands, tokens);
	sllist_free(tokens, token_free);
}
