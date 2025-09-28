/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_get_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 02:45:29 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/26 02:51:24 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "ft_string.h"

t_slnode *environ_get_node(t_sllist *list, const char *name)
{
	t_slnode *current;
	size_t name_len;
	char *env_str;

	name_len = ft_strlen(name);
	current = list->head;
	while (current)
	{
		env_str = (char *)current->data;
		if (ft_strncmp(env_str, name, name_len) == 0 && env_str[name_len] == '=')
			return (current);
		current = current->next;
	}
	return (NULL);
}
