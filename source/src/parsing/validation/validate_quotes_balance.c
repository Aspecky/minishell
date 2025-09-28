/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quotes_balance.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:03:57 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/28 20:45:00 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "parsing.h"
#include <stddef.h>

bool	validate_quotes_balance(const char *str)
{
	char	*ptr;
	char	quote;

	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			quote = *str;
			ptr = ft_strchr(++str, quote);
			if (!ptr)
				return (false);
			str = ptr + 1;
		}
		else
			str++;
	}
	return (true);
}
