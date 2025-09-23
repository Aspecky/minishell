/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expantion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:59:25 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/23 22:01:05 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.h"
#include "ft_ctype.h"
#include "ft_stdlib.h"
#include "parsing.h"
#include <errno.h>

static size_t get_variable_name_length(char *str)
{
	size_t len;

	len = 0;
	while (str[len] && ft_isalnum(str[len]))
		len++;
	return (len);
}

static void append_char_to_vector(t_vector *vector, char c)
{
	vector_set(vector, vector->size, &c);
}

static void append_string_to_vector(t_vector *vector, char *str)
{
	while (*str)
	{
		append_char_to_vector(vector, *str);
		str++;
	}
}

char *param_expantion(char *str, char *const envp[])
{
	t_vector vector;
	int old_errno;
	bool in_double_quotes;

	if (!vector_init(&vector, 0, sizeof(char)))
		return (0);
	old_errno = errno;
	errno = 0;
	in_double_quotes = false;
	while (*str)
	{
		if (*str == '\'' && !in_double_quotes)
		{
			char quote = *str;
			// Add the opening quote
			append_char_to_vector(&vector, *str);
			str++;
			// Process until closing quote
			while (*str != quote)
			{
				append_char_to_vector(&vector, *str);
				str++;
			}
			append_char_to_vector(&vector, *str);
			str++;
		} else if (*str == '$')
		{
			size_t var_len = get_variable_name_length(str + 1);
			char *param;
			char tmp;

			if (var_len == 0)
			{
				// $ followed by word separator, keep the $
				append_char_to_vector(&vector, *str);
				str++;
			} else
			{
				tmp = str[1 + var_len];
				str[1 + var_len] = 0;
				param = getenv_r(str + 1, envp);
				if (param)
					append_string_to_vector(&vector, param);
				// else: variable not found, expand to nothing (don't copy
				// anything)
				str[1 + var_len] = tmp;
				str += 1 + var_len;
			}
		} else
		{
			if (*str == '"')
				in_double_quotes = !in_double_quotes;
			append_char_to_vector(&vector, *str);
			str++;
		}
	}

	append_char_to_vector(&vector, 0);
	if (errno)
		return (free(vector.arr), NULL);
	errno = old_errno;
	return (vector.arr); // return the internal array
}
