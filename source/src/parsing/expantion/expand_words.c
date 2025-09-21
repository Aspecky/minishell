/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:56:33 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/21 21:29:45 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "parsing.h"
#include <stdio.h>

static size_t get_variable_name_length(char *str)
{
	size_t len;

	len = 0;
	while (str[len] && !is_word_separator(str[len]) && str[len] != '\"' && str[len] != '$')
		len++;
	return (len);
}

static size_t get_quoted_length(char *str)
{
	size_t len;
	char quote;

	quote = *str;
	len = 1; // for opening quote
	str++;
	while (*str != quote)
	{
		len++;
		str++;
	}
	len++; // for closing quote
	return (len);
}

static size_t count_expantion_length(char *str, char *const envp[])
{
	size_t len;

	len = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			size_t quote_len = get_quoted_length(str);
			len += quote_len;
			str += quote_len;
		} else if (*str == '$')
		{
			// TODO: Handle $?
			size_t var_len = get_variable_name_length(str + 1);
			char *param;
			char tmp;

			if (var_len == 0)
			{
				// $ followed by word separator, keep the $
				len++;
				str++;
			}
			else
			{
				tmp = str[1 + var_len];
				str[1 + var_len] = 0;
				param = getenv_r(str + 1, envp);
				if (param)
					len += ft_strlen(param);
				// else: variable not found, expand to nothing (contribute 0 bytes)
				str[1 + var_len] = tmp;
				str += 1 + var_len;
			}
		} else
		{
			len++;
			str++;
		}
	}
	return (len);
}

char *expand_word(char *str, char *const envp[])
{
	char *word;
	char *word_ptr;
	size_t len;

	len = count_expantion_length(str, envp);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (0);
	word_ptr = word;
	while (*str)
	{
		if (*str == '\'')
		{
			size_t quote_len = get_quoted_length(str);
			ft_memcpy(word_ptr, str, quote_len);
			word_ptr += quote_len;
			str += quote_len;
		} else if (*str == '$')
		{
			size_t var_len = get_variable_name_length(str + 1);
			char *param;
			char tmp;

			if (var_len == 0)
			{
				// $ followed by word separator, keep the $
				*word_ptr++ = *str++;
			}
			else
			{
				tmp = str[1 + var_len];
				str[1 + var_len] = 0;
				param = getenv_r(str + 1, envp);
				if (param)
				{
					// TODO: Implement ft_strcpy
					while (*param)
						*word_ptr++ = *param++;
				}
				// else: variable not found, expand to nothing (don't copy anything)
				str[1 + var_len] = tmp;
				str += 1 + var_len;
			}
		} else
		{
			*word_ptr++ = *str++;
		}
	}
	*word_ptr = 0;
	return (word);
}

bool expand_words(t_sllist *tokens, char *const envp[])
{
	t_slnode *node;
	t_token *token;
	char *expanded;

	node = tokens->head;
	while (node)
	{
		token = node->data;
		if (token->type == TOKEN_WORD)
		{
			expanded = expand_word(token->value, envp);
			if (!expanded)
				return (false);
			free(token->value);
			token->value = expanded;
		}
		node = node->next;
	}
	return (true);
}
