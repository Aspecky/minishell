/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:27:23 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/16 17:18:40 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "utils.h"
#include <stdlib.h>

extern char **environ;

void env_free(char **env, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char **envdup(void)
{
	char **env;
	size_t len;
	size_t i;

	len = 0;
	while (environ[len])
		len++;
	env = malloc(sizeof(char *) * (len + 1));
	if (!env)
		return (0);
	i = 0;
	while (i < len)
	{
		env[i] = ft_strdup(environ[i]);
		if (!env[i])
		{
			env_free(env, i);
			return (0);
		}
		i++;
	}
	env[i] = 0;
	return (env);
}
