/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_list_to_envp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:54:34 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/25 17:16:22 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include <stdlib.h>

char	**environ_list_to_envp(t_sllist *list)
{
	char		**envp;
	t_slnode	*node;
	size_t		i;

	envp = malloc(sizeof(char *) * (list->size + 1));
	if (!envp)
		return (0);
	node = list->head;
	i = 0;
	while (i < list->size)
	{
		envp[i] = node->data;
		node = node->next;
		i++;
	}
	envp[i] = 0;
	return (envp);
}
