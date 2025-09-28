/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expantion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:59:25 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/28 22:11:25 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.h"
#include "parsing.h"
#include <errno.h>
#include <stdlib.h>

static void	handle_single_quotes(char **str, t_vector *vector)
{
	char	quote;

	quote = **str;
	vector_set(vector, vector->size, *str);
	(*str)++;
	while (**str != quote)
	{
		vector_set(vector, vector->size, *str);
		(*str)++;
	}
	vector_set(vector, vector->size, *str);
	(*str)++;
}

char	*param_expantion(char *str, char *const envp[])
{
	t_vector	vector;
	int			old_errno;
	bool		in_double_quotes;

	if (!vector_init(&vector, 0, sizeof(char)))
		return (0);
	((void)0, old_errno = errno, errno = 0, in_double_quotes = false);
	while (*str)
	{
		if (*str == '\'' && !in_double_quotes)
			handle_single_quotes(&str, &vector);
		else if (*str == '$')
			expand_variable(&str, envp, &vector);
		else
		{
			if (*str == '"')
				in_double_quotes = !in_double_quotes;
			(vector_set(&vector, vector.size, str), str++);
		}
	}
	vector_set(&vector, vector.size, &(char){0});
	if (errno)
		return (free(vector.arr), NULL);
	return ((void)0, errno = old_errno, vector.arr);
}
