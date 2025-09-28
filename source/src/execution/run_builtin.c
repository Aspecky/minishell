/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:48:08 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/26 20:22:18 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_string.h"
#include <stdlib.h>

int run_builtin(t_cmd *cmd, t_environ *env)
{
	const char *name;

	name = cmd->argv[0];
	if (ft_strcmp(name, "cd") == 0)
		return (cd_builtin(cmd->argc, cmd->argv, env));
	else if (ft_strcmp(name, "pwd") == 0)
		return (pwd_builtin());
	else if (ft_strcmp(name, "echo") == 0)
		return (echo_builtin(cmd->argc, cmd->argv));
	else if (ft_strcmp(name, "exit") == 0)
		return (exit_builtin(cmd->argc, cmd->argv));
	else if (ft_strcmp(name, "env") == 0)
		return (env_builtin(env->arr));
	else if (ft_strcmp(name, "unset") == 0)
		return (unset_builtin(cmd->argc, cmd->argv, env));
	else if (ft_strcmp(name, "export") == 0)
		return (export_builtin(cmd->argc, cmd->argv, env));
	return (EXIT_FAILURE);
}
