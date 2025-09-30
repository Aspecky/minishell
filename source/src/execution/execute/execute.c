/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:15:51 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/30 22:48:14 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"
#include "execution.h"
#include "ft_stdio.h"
#include "minishell.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

static int	waitpid_eintr(pid_t pid, int *wstatus, int options)
{
	int	ret;

	ret = waitpid(pid, wstatus, options);
	if (ret == -1 && errno == EINTR)
		return (waitpid_eintr(pid, wstatus, options));
	return (ret);
}

static bool	wait_on_children(pid_t last_pid)
{
	int	wstatus;
	int	estatus;
	int	pid;

	while (true)
	{
		pid = waitpid_eintr(-1, &wstatus, 0);
		if (pid == -1)
		{
			if (errno != ECHILD)
				return (print_error("execution", "waitpid: %s",
						strerror(errno)), false);
			break ;
		}
		if (WIFEXITED(wstatus))
			estatus = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
		{
			printf("\n");
			estatus = 128 + WTERMSIG(wstatus);
		}
		if (pid == last_pid)
			g_last_exit_status = estatus;
	}
	return (true);
}

static bool	maybe_pipe(bool next, int fds[2], int prev_stdin, t_cmd *cmd)
{
	if (next)
	{
		if (pipe(fds) == -1)
		{
			if (prev_stdin != STDIN)
				close(prev_stdin);
			print_error("execution", "pipe: %s", strerror(errno));
			return (false);
		}
		cmd->stdout_fd = dup(fds[STDOUT]);
	}
	return (true);
}

static void	cleanup_fds(int *prev_stdin, bool next, int fds[2], t_cmd *cmd)
{
	if (*prev_stdin != STDIN)
		close(*prev_stdin);
	if (next)
	{
		*prev_stdin = fds[STDIN];
		close(fds[STDOUT]);
		close(cmd->stdout_fd);
	}
	if (cmd->stdin_fd != STDIN)
		close(cmd->stdin_fd);
	close(cmd->heredoc_fd);
}

void	execute(t_sllist *commands, t_environ *env)
{
	t_execute_vars	vars;

	vars.last_pid = -1;
	vars.prev_stdin = STDIN;
	vars.current = commands->head;
	while (vars.current)
	{
		vars.cmd = vars.current->data;
		vars.next = vars.current->next;
		if (vars.cmd->stdin_fd == STDIN)
			vars.cmd->stdin_fd = vars.prev_stdin;
		if (!maybe_pipe(vars.next, vars.fds, vars.prev_stdin, vars.cmd))
			break ;
		if (vars.cmd->argv[0])
		{
			if (commands->size == 1 && is_builtin(vars.cmd->argv[0]))
				exec_builtin(vars.cmd, vars.fds, env);
			else if (!exec_fork(&vars, env))
				break ;
		}
		cleanup_fds(&vars.prev_stdin, vars.next, vars.fds, vars.cmd);
		vars.current = vars.next;
	}
	wait_on_children(vars.last_pid);
}
