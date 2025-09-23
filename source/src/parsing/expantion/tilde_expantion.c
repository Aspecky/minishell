/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expantion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:56:40 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/23 22:18:00 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.h"
#include "ft_string.h"
#include "parsing.h"
#include <stdio.h>

char *tilde_expantion(char *str, char *const envp[])
{
	t_vector vector;
	if (!(str[0] == '~' && (str[1] == '/' || !str[1])))
		return (ft_strdup(str));

	// vector_init(&vector, 0, sizeof(char));
	printf("tilde: '%s'\n", str);
	return (ft_strdup(str));
	return (vector.arr);
}
