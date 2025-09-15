/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 00:00:00 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/15 21:39:28 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_string.h"
#include "lexer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

size_t count_word_length(const char *stream)
{
	char *ptr;
	char quote;
	size_t len;
	size_t spn;

	len = 0;
	while (*stream && !ft_isspace(*stream) && !is_special_char(*stream))
	{
		if (*stream == '\'' || *stream == '"')
		{
			quote = *stream;
			ptr = ft_strchr(++stream, quote);
			len += ptr - stream;
			stream = ptr + 1;
		} else
		{
			spn = ft_strcspn(stream, "\t \"\'<>|");
			len += spn;
			stream += spn;
		}
	}
	return (len);
}

static char *extract_complete_word(char **stream)
{
	char *result = NULL;
	size_t total_len = 0;

	result = malloc(count_word_length(*stream) + 1);
	if (!result)
		return (NULL);

	while (**stream && !ft_isspace(**stream) && !is_special_char(**stream))
	{
		if (**stream == '\'' || **stream == '"')
		{
			// Extract quoted part
			char quote = **stream;
			(*stream)++; // Skip opening quote

			while (**stream && **stream != quote)
			{
				result[total_len++] = **stream;
				(*stream)++;
			}
			(*stream)++; // Skip closing quote
		} else
		{
			// Extract unquoted part
			while (**stream && !ft_isspace(**stream) &&
				   !is_special_char(**stream) && **stream != '\'' &&
				   **stream != '"')
			{
				result[total_len++] = **stream;
				(*stream)++;
			}
		}
	}
	result[total_len] = '\0';
	return (result);
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
			type = TOKEN_REDIRECT_IN;
			value = ft_strdup("<");
			stream++;
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
			value = extract_complete_word(&stream);
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
