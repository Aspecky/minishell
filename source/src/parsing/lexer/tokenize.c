/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 00:00:00 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/28 21:36:21 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_string.h"
#include "parsing.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static char	*extract_word(char **stream)
{
	char	*word;
	char	*ptr;
	char	quote;
	size_t	len;

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
		}
		else
			ptr++;
	}
	len = ptr - *stream;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (0);
	(ft_memcpy(word, *stream, len), word[len] = 0, *stream = ptr);
	return (word);
}

static void	parse_token(char **stream, t_token_type *type, char **value)
{
	*type = TOKEN_EOF;
	if (ft_isspace(**stream))
		(*stream)++;
	else if (**stream == '|')
		((void)0, *type = TOKEN_PIPE, *value = ft_strdup("|"), (*stream)++);
	else if (**stream == '<')
		if (*((*stream) + 1) == '<')
			((void)0, *type = TOKEN_HEREDOC, *value = ft_strdup("<<"), *stream
				+= 2);
	else
		((void)0, *type = TOKEN_REDIRECT_IN, *value = ft_strdup("<"),
			(*stream)++);
	else if (**stream == '>')
		if (*((*stream) + 1) == '>')
			((void)0, *type = TOKEN_REDIRECT_APPEND, *value = ft_strdup(">>"),
				*stream += 2);
	else
		((void)0, *type = TOKEN_REDIRECT_OUT, *value = ft_strdup(">"),
			(*stream)++);
	else
		((void)0, *type = TOKEN_WORD, *value = extract_word(stream));
}

static bool	append_eof_token(t_sllist *tokens)
{
	t_token	*token;

	token = token_new(TOKEN_EOF, 0);
	if (!token)
		return (false);
	if (!sllist_append(tokens, token))
		return (token_free(token), false);
	return (true);
}

bool	tokenize(char *stream, t_sllist *tokens)
{
	t_token			*token;
	char			*value;
	t_token_type	type;

	while (*stream)
	{
		parse_token(&stream, &type, &value);
		if (type != TOKEN_EOF)
		{
			if (!value)
				return (false);
			token = token_new(type, value);
			if (!token || !sllist_append(tokens, token))
			{
				if (token)
					token_free(token);
				return (false);
			}
		}
	}
	return (append_eof_token(tokens));
}
