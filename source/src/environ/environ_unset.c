/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:05:29 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/27 18:49:32 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include <stdlib.h>

bool	environ_unset(t_environ *env, const char *name)
{
	t_slnode	*node_to_remove;
	char		**new_arr;

	node_to_remove = environ_get_node(env->list, name);
	if (!node_to_remove)
		return (true);
	sllist_pop(env->list, node_to_remove, 0);
	slnode_free(node_to_remove, free);
	new_arr = environ_list_to_envp(env->list);
	if (!new_arr)
		return (false);
	free(env->arr);
	env->arr = new_arr;
	return (true);
}
