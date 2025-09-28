/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expantion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:41:23 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/28 22:35:22 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.h"
#include "parsing.h"
#include <errno.h>
#include <stdlib.h>

char	*heredoc_expantion(char *str, char *const envp[], ssize_t *len)
{
	t_vector	vector;
	int			old_errno;

	if (!vector_init(&vector, 0, sizeof(char)))
		return (0);
	old_errno = errno;
	errno = 0;
	while (*str)
	{
		if (*str == '$')
			expand_variable(&str, envp, &vector);
		else
		{
			vector_set(&vector, vector.size, str);
			str++;
		}
	}
	vector_set(&vector, vector.size, &(char){0});
	*len = (ssize_t)vector.size - 1;
	if (errno)
		return (free(vector.arr), NULL);
	errno = old_errno;
	return (vector.arr);
}
