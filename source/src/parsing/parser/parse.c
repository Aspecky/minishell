/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:13:46 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/16 01:10:48 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_debug.h"
#include "lexer.h"
#include "parser.h"
#include "validation.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

t_sllist *parse(char *stream)
{
	t_sllist *tokens;
	t_sllist *commands;

	if (!check_quotes_balance(stream))
		return (NULL);
	// TODO: Add $ expantion
	tokens = tokenize(stream);
	if (!tokens)
		return (NULL);
	print_tokens(tokens);
	if (!check_redirections(tokens))
		return (sllist_free(tokens, token_free), NULL);
	commands = tokens_to_commands(tokens);
	sllist_free(tokens, token_free);
	return (commands);
}
