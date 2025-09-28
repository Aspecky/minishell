/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 01:53:32 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/19 02:13:53 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "ft_string.h"
#include <stdlib.h>

extern char	**environ;

t_environ	*environ_new(void)
{
	t_environ	*env;
	size_t		len;
	size_t		i;
	char		*dup;

	len = 0;
	while (environ[len])
		len++;
	env = malloc(sizeof(t_environ));
	if (!env)
		return (0);
	env->list = sllist_new();
	env->arr = malloc(sizeof(char *) * (len + 1));
	if (!env || !env->list || !env->arr)
		return (free(env->list), free(env->arr), NULL);
	i = 0;
	while (i < len)
	{
		dup = ft_strdup(environ[i]);
		if (!dup || !sllist_append(env->list, dup))
			return (free(dup), environ_free(env), NULL);
		env->arr[i++] = dup;
	}
	env->arr[i] = 0;
	return (env);
}
