/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 22:35:16 by hasbayou          #+#    #+#             */
/*   Updated: 2025/10/01 15:43:17 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"
#include "execution.h"
#include "ft_stdio.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

static void	reset_signals(int sigs[])
{
	while (*sigs)
	{
		signal(*sigs, SIG_DFL);
		sigs++;
	}
}

static bool	on_fork_error(int prev_stdin, bool next, int fds[2], t_cmd *cmd)
{
	if (prev_stdin != STDIN)
		close(prev_stdin);
	if (next)
	{
		close(fds[STDIN]);
		close(fds[STDOUT]);
		close(cmd->stdout_fd);
	}
	print_error("execution", "fork: %s", strerror(errno));
	return (false);
}

static void	handle_child(t_cmd *cmd, int fds[2], bool next, t_environ *env)
{
	int		status;
	char	*errmsg;

	if (!open_cmd_redirs(cmd))
		exit(EXIT_FAILURE);
	redirect_io(cmd, fds, next);
	reset_signals((int []){SIGINT, SIGQUIT, SIGTERM, 0});
	if (is_builtin(cmd->argv[0]))
		exit(run_builtin(cmd, env));
	else
	{
		ft_execvpe(cmd->argv[0], cmd->argv, env->arr);
		status = EXIT_FAILURE;
		errmsg = strerror(errno);
		if (errno == ENOENT)
		{
			errmsg = "command not found";
			status = 127;
		}
		else if (errno == EACCES)
			status = 126;
		print_error(cmd->argv[0], errmsg);
		exit(status);
	}
}

bool	exec_fork(t_execute_vars *vars, t_environ *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (on_fork_error(vars->prev_stdin, vars->next != NULL, vars->fds,
				vars->cmd));
	vars->last_pid = pid;
	if (pid == 0)
		handle_child(vars->cmd, vars->fds, vars->next != NULL, env);
	return (true);
}
