/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:15:51 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/28 15:24:46 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"
#include "environ.h"
#include "execution.h"
#include "ft_stdio.h"
#include "minishell.h"
#include "signal_hooks.h"
#include "utils.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void redirect_io(t_cmd *cmd, int fds[2], bool close_pipe)
{
	if (cmd->stdin_fd != STDIN)
	{
		dup2(cmd->stdin_fd, STDIN);
		close(cmd->stdin_fd);
	}
	if (cmd->stdout_fd != STDOUT)
	{
		dup2(cmd->stdout_fd, STDOUT);
		close(cmd->stdout_fd);
	}
	if (close_pipe)
	{
		close(fds[STDIN]);
		close(fds[STDOUT]);
	}
}

bool wait_on_children(pid_t last_pid)
{
	int wstatus;

	if (last_pid != -1 && waitpid(last_pid, &wstatus, 0) != -1)
	{
		if (WIFEXITED(wstatus))
			g_last_exit_status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
		{
			g_last_exit_status = 128 + WTERMSIG(wstatus);
			if (WTERMSIG(wstatus) == SIGTERM)
				exit(g_last_exit_status);
		}
	}
	while (true)
		if (wait(0) == -1)
			break;
	return (true);
}

static void exec_builtin(t_cmd *cmd, int fds[2], t_environ *env)
{
	int saved_stdin;
	int saved_stdout;

	if (!open_cmd_redirs(cmd))
		return;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);

	// Setup redirection for the builtin
	redirect_io(cmd, fds, false);
	g_last_exit_status = run_builtin(cmd, env);

	// Restore original file descriptors
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

bool execute(t_sllist *commands, t_environ *env)
{
	t_slnode *current;
	t_slnode *next;
	t_cmd *cmd;
	int fds[2];
	pid_t pid;
	pid_t last_pid;
	int prev_stdin;

	is_executing = true;
	pid = -1;
	last_pid = -1;
	prev_stdin = STDIN;
	current = commands->head;
	while (current)
	{
		cmd = current->data;
		next = current->next;

		if (cmd->stdin_fd == STDIN)
			cmd->stdin_fd = prev_stdin;
		if (next)
		{
			if (pipe(fds) == -1)
			{
				if (prev_stdin != STDIN)
					close(prev_stdin);
				print_error("execution", "pipe: %s", strerror(errno));
				break;
			}
			cmd->stdout_fd = dup(fds[STDOUT]);
		}
		if (cmd->argv[0])
		{
			if (commands->size == 1 && is_builtin(cmd->argv[0]))
				exec_builtin(cmd, fds, env);
			else
			{
				pid = fork();
				if (pid == -1)
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
					break;
				}
				last_pid = pid;
				if (pid == 0)
				{
					if (!open_cmd_redirs(cmd))
						exit(EXIT_FAILURE);
					redirect_io(cmd, fds, next);
					hook_child_signals();

					if (is_builtin(cmd->argv[0]))
						exit(run_builtin(cmd, env));
					else
					{
						int status;
						char *errmsg;

						ft_execvpe(cmd->argv[0], cmd->argv, env->arr);
						status = EXIT_FAILURE;
						errmsg = strerror(errno);
						if (errno == ENOENT)
						{
							errmsg = "command not found";
							status = 127;
						} else if (errno == EACCES)
							status = 126;
						print_error(cmd->argv[0], errmsg);
						exit(status);
					}
				}
			}
		}

		if (prev_stdin != STDIN)
			close(prev_stdin);
		if (next)
		{
			prev_stdin = fds[STDIN];
			close(fds[STDOUT]);
			close(cmd->stdout_fd);
		}
		current = next;
	}

	wait_on_children(last_pid);
	is_executing = false;
	return (true);
}
