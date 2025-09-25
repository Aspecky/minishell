/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:14:12 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/25 18:01:37 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "execution.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int cd_builtin(int ac, char *av[], t_environ *env)
{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;
	int		status;

	/* Save current directory before changing */
	old_pwd = getcwd(0, 0);
	
	/* Determine target directory */
	if (ac == 1)
	{
		path = getenv_r("HOME", env->arr);
		if (!path)
			return (free(old_pwd), EXIT_FAILURE);
	}
	else if (ft_strcmp(av[1], "-") == 0)
	{
		path = getenv_r("OLDPWD", env->arr);
		if (!path)
		{
			perror("cd: OLDPWD not set");
			return (free(old_pwd), EXIT_FAILURE);
		}
	}
	else
		path = av[1];

	/* Change directory */
	if (chdir(path) == -1)
	{
		perror("cd: chdir");
		return (free(old_pwd), EXIT_FAILURE);
	}

	/* Update environment variables */
	status = EXIT_SUCCESS;
	if (old_pwd && !environ_set(env, "OLDPWD", old_pwd))
		status = EXIT_FAILURE;
	free(old_pwd);
	
	new_pwd = getcwd(0, 0);
	if (new_pwd && !environ_set(env, "PWD", new_pwd))
		status = EXIT_FAILURE;
	free(new_pwd);
	
	return (status);
}
