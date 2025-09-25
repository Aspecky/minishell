/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expantion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:59:25 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/25 19:42:06 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.h"
#include "parsing.h"
#include <errno.h>
#include <stdlib.h>

static void append_char_to_vector(t_vector *vector, char c)
{
	vector_set(vector, vector->size, &c);
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
			expand_variable(&str, envp, &vector);
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
