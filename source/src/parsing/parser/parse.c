/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:13:46 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/15 21:23:36 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "_debug.h"
#include "lexer.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

t_sllist *parse(char *stream)
{
	t_sllist *tokens;
	t_sllist *commands;

	// Step 1: Tokenize the input
	tokens = tokenize(stream);
	if (!tokens)
		return (NULL);

	print_tokens(tokens);

	// Step 2: Group tokens into commands (split by pipes)
	commands = tokens_to_commands(tokens);

	sllist_free(tokens, token_free);

	return (commands);
}
