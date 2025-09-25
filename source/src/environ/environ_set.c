/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:05:29 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/25 17:19:38 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "ft_string.h"
#include <stdlib.h>

static char *create_env_entry(const char *name, const char *value)
{
	size_t name_len;
	size_t value_len;
	char *entry;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	entry = malloc(name_len + value_len + 2);
	if (!entry)
		return (NULL);
	ft_memcpy(entry, name, name_len);
	entry[name_len] = '=';
	ft_memcpy(entry + name_len + 1, value, value_len);
	entry[name_len + value_len + 1] = '\0';
	return (entry);
}

static t_slnode *find_env_node(t_sllist *list, const char *name)
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

bool environ_set(t_environ *env, const char *name, const char *value)
{
	t_slnode *existing_node;
	char *new_entry;
	char **new_arr;

	new_entry = create_env_entry(name, value);
	if (!new_entry)
		return (false);
	existing_node = find_env_node(env->list, name);
	if (existing_node)
	{
		free(existing_node->data);
		existing_node->data = new_entry;
	}
	else
	{
		if (!sllist_append(env->list, new_entry))
		{
			free(new_entry);
			return (false);
		}
	}
	new_arr = environ_list_to_envp(env->list);
	if (!new_arr)
		return (false);
	free(env->arr);
	env->arr = new_arr;
	return (true);
}
