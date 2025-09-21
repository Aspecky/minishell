/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 00:00:00 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/20 22:28:49 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_string.h"
#include "parsing.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char *extract_word(char **stream)
{
	char *word;
	char *ptr;
	char quote;
	size_t len;

	ptr = *stream;
	while (*ptr && !is_word_separator(*ptr))
	{
		if (is_quote(*ptr))
		{
			quote = *ptr++;
			while (*ptr && *ptr != quote)
				ptr++;
			if (*ptr == quote)
				ptr++;
		} else
			ptr++;
	}
	len = ptr - *stream;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (0);
	ft_memcpy(word, *stream, len);
	word[len] = 0;
	*stream = ptr;
	return (word);
}

t_sllist *tokenize(char *stream)
{
	t_sllist *tokens;
	t_token *token;
	char *value;
	t_token_type type;

	tokens = sllist_new();
	if (!tokens)
		return (NULL);
	while (*stream)
	{
		type = TOKEN_EOF;

		// Skip whitespace
		if (ft_isspace(*stream))
			stream++;
		// Handle pipe
		else if (*stream == '|')
		{
			type = TOKEN_PIPE;
			value = ft_strdup("|");
			stream++;
		}
		// Handle redirections
		else if (*stream == '<')
		{
			if (*(stream + 1) == '<')
			{
				type = TOKEN_HEREDOC;
				value = ft_strdup("<<");
				stream += 2;
			} else
			{
				type = TOKEN_REDIRECT_IN;
				value = ft_strdup("<");
				stream++;
			}
		} else if (*stream == '>')
		{
			if (*(stream + 1) == '>')
			{
				type = TOKEN_REDIRECT_APPEND;
				value = ft_strdup(">>");
				stream += 2;
			} else
			{
				type = TOKEN_REDIRECT_OUT;
				value = ft_strdup(">");
				stream++;
			}
		}
		// Handle regular words (including mixed quoted/unquoted)
		else
		{
			type = TOKEN_WORD;
			value = extract_word(&stream);
		}

		// Create token and add to list (only if we have a valid type)
		if (type != TOKEN_EOF)
		{
			if (!value)
			{
				sllist_free(tokens, token_free);
				return (NULL);
			}
			token = token_new(type, value);
			if (!token || !sllist_append(tokens, token))
			{
				if (token)
					token_free(token);
				return (sllist_free(tokens, token_free), NULL);
			}
		}
	}
	token = token_new(TOKEN_EOF, 0);
	if (!token)
		return (sllist_free(tokens, token_free), NULL);
	if (!sllist_append(tokens, token))
		return (token_free(token), sllist_free(tokens, token_free), NULL);
	return (tokens);
}
