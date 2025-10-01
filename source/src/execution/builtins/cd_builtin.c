/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:14:12 by hasbayou          #+#    #+#             */
/*   Updated: 2025/10/01 15:42:55 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "execution.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "utils.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char	*get_cd_path(int ac, char *av[], t_environ *env)
{
	char	*path;

	if (ac == 1)
	{
		path = getenv_r("HOME", env->arr);
		if (!path)
			print_error("cd", "HOME not set");
	}
	else if (ft_strcmp(av[1], "-") == 0)
	{
		path = getenv_r("OLDPWD", env->arr);
		if (!path)
			print_error("cd", "OLDPWD not set");
	}
	else
		path = av[1];
	return (path);
}

static int	update_pwd_vars(t_environ *env, char *old_pwd)
{
	char	*new_pwd;
	int		status;

	status = EXIT_SUCCESS;
	if (!(old_pwd && environ_set(env, "OLDPWD", old_pwd)))
	{
		print_error("cd", "failed to set OLDPWD: %s", strerror(errno));
		status = EXIT_FAILURE;
	}
	new_pwd = getcwd(0, 0);
	if (!(new_pwd && environ_set(env, "PWD", new_pwd)))
	{
		print_error("cd", "failed to set PWD: %s", strerror(errno));
		status = EXIT_FAILURE;
	}
	free(new_pwd);
	return (status);
}

int	cd_builtin(int ac, char *av[], t_environ *env)
{
	char	*path;
	char	*old_pwd;
	int		status;

	old_pwd = getcwd(0, 0);
	path = get_cd_path(ac, av, env);
	if (!path)
		return (free(old_pwd), EXIT_FAILURE);
	if (chdir(path) == -1)
	{
		print_error("cd", "%s: %s", path, strerror(errno));
		return (free(old_pwd), EXIT_FAILURE);
	}
	status = update_pwd_vars(env, old_pwd);
	free(old_pwd);
	return (status);
}
