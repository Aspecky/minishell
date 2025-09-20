/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:03:57 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/20 18:00:13 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "parsing.h"
#include <stddef.h>
#include <stdio.h>

bool check_quotes_balance(const char *str)
{
	char *ptr;
	char quote;
	const char *start;
	size_t position;

	start = str;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			quote = *str;
			position = str - start + 1;
			ptr = ft_strchr(++str, quote);
			if (!ptr)
			{
				printf("syntax error: unclosed quote (%c) at position %zu\n",
					   quote, position);
				printf("%s\n", start);
				printf("%*s^\n", (int)(position - 1), "");
				return (false);
			}
			str = ptr + 1;
		} else
			str++;
	}
	return (true);
}
