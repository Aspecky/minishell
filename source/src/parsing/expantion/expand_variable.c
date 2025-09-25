/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 00:00:00 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/25 19:50:58 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.h"
#include "ft_ctype.h"
#include "ft_stdlib.h"
#include "minishell.h"

static size_t get_variable_name_length(char *str)
{
	size_t len;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}

static void append_string_to_vector(t_vector *vector, char *str)
{
	while (*str)
	{
		vector_set(vector, vector->size, str);
		str++;
	}
}

char *expand_variable(char **str, char *const envp[], t_vector *vector)
{
	size_t var_len;
	char *param;
	char tmp;

	// Handle $? special case
	if ((*str)[1] == '?')
	{
		param = ft_itoa(g_last_exit_status);
		if (param)
		{
			append_string_to_vector(vector, param);
			free(param);
		}
		*str += 2; // Skip $ and ?
		return (*str);
	}

	var_len = get_variable_name_length(*str + 1);
	if (var_len == 0)
	{
		// $ followed by word separator, keep the $
		vector_set(vector, vector->size, *str);
		(*str)++;
	}
	else
	{
		tmp = (*str)[1 + var_len];
		(*str)[1 + var_len] = 0;
		param = getenv_r(*str + 1, envp);
		if (param)
			append_string_to_vector(vector, param);
		// else: variable not found, expand to nothing (don't copy anything)
		(*str)[1 + var_len] = tmp;
		*str += 1 + var_len;
	}
	return (*str);
}
