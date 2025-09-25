/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:15:51 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/25 06:00:49 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"
#include "execution.h"
#include "minishell.h"
#include "signal_hooks.h"
#include "environ.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

bool open_cmd_redirs(t_cmd *cmd)
{
	t_redir *redir;
	t_slnode *node;

	node = cmd->redirs->head;
	while (node)
	{
		redir = node->data;
		if (redir->type == REDIR_IN)
		{
			if (cmd->stdin_fd != STDIN)
				close(cmd->stdin_fd);
			cmd->stdin_fd = open(redir->file_or_delim, O_RDONLY);
			if (cmd->stdin_fd == -1)
				return (perror("redirection <"), false);
		} else if (redir->type == REDIR_OUT)
		{
			if (cmd->stdout_fd != STDOUT)
				close(cmd->stdout_fd);
			cmd->stdout_fd =
				open(redir->file_or_delim, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (cmd->stdout_fd == -1)
				return (perror("redirection >"), false);
		} else if (redir->type == REDIR_APPEND)
		{
			if (cmd->stdout_fd != STDOUT)
				close(cmd->stdout_fd);
			cmd->stdout_fd =
				open(redir->file_or_delim, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (!cmd->stdout_fd)
				return (perror("redirection >>"), false);
		}
		node = node->next;
	}
	return (true);
}

bool setup_cmd_io(t_cmd *cmd, int fds[2], bool close_pipe)
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
	return (true);
}



bool wait_on_children(size_t children_count, pid_t last_pid)
{
	int wstatus;
	size_t i;

	if (waitpid(last_pid, &wstatus, 0) != -1)
	{
		if (WIFEXITED(wstatus))
			g_last_exit_status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			g_last_exit_status = 128 + WTERMSIG(wstatus);
	} else
		perror("waitpid");
	i = 0;
	while (i < children_count - 1)
	{
		if (wait(0) == -1)
			perror("wait");
		i++;
	}
	return (true);
}

bool execute(t_sllist *commands, t_environ *env)
{
	t_slnode *current;
	t_slnode *next;
	t_cmd *cmd;
	int fds[2];
	pid_t pid;
	int prev_stdin;

	pid = -1;
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
			pipe(fds);
			cmd->stdout_fd = dup(fds[STDOUT]);
		}

		if (commands->size == 1 && is_builtin(cmd->argv[0]))
		{
			g_last_exit_status = run_builtin(cmd, env);
		}
		else
		{
			pid = fork();
			if (pid == -1)
				perror("fork");
			if (pid == 0)
			{
				if (!open_cmd_redirs(cmd))
					exit(EXIT_FAILURE);
				if (!setup_cmd_io(cmd, fds, next))
					exit(EXIT_FAILURE);
				hook_child_signals();

				if (is_builtin(cmd->argv[0]))
					exit(run_builtin(cmd, env));
				else
				{
					ft_execvpe(cmd->argv[0], cmd->argv, env->arr);
					return (perror("execute"), exit(EXIT_FAILURE), false);
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

	if (pid != -1)
		wait_on_children(commands->size, pid);
	return (true);
}
