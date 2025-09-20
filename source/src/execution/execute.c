/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:15:51 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/20 15:51:45 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"
#include "execution.h"
#include "signal_hooks.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

bool setup_cmd_io(t_cmd *cmd)
{
	t_redir *redir;
	t_slnode *node;

	node = cmd->redirs->head;
	while (node)
	{
		redir = node->data;
		if (redir->type == REDIR_IN)
		{
			if (cmd->stdin != STDIN)
				close(cmd->stdin);
			cmd->stdin = open(redir->file_or_delim, O_RDONLY);
			if (cmd->stdin == -1)
				return (perror("redirection <"), false);
		} else if (redir->type == REDIR_OUT)
		{
			if (cmd->stdout != STDOUT)
				close(cmd->stdout);
			cmd->stdout =
				open(redir->file_or_delim, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (cmd->stdout == -1)
				return (perror("redirection >"), false);
		} else if (redir->type == REDIR_APPEND)
		{
			if (cmd->stdout != STDOUT)
				close(cmd->stdout);
			cmd->stdout =
				open(redir->file_or_delim, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (!cmd->stdout)
				return (perror("redirection >>"), false);
		}
		node = node->next;
	}
	return (true);
}

typedef struct s_execute {

} t_execute;

bool execute(t_sllist *commands, char *const envp[])
{
	t_slnode *current;
	t_slnode *next;
	t_cmd *cmd;
	int fds[2];
	int pid;
	int prev_stdin;
	size_t i;

	prev_stdin = STDIN;
	current = commands->head;
	while (current)
	{
		cmd = current->data;
		next = current->next;

		if (cmd->stdin == STDIN)
			cmd->stdin = prev_stdin;
		if (next)
		{
			pipe(fds);
			cmd->stdout = dup(fds[STDOUT]);
		}
		pid = fork();
		if (pid == 0)
		{
			if (!setup_cmd_io(cmd))
				exit(EXIT_FAILURE);
			if (cmd->stdin != STDIN)
			{
				dup2(cmd->stdin, STDIN);
				close(cmd->stdin);
			}
			if (cmd->stdout != STDOUT)
			{
				dup2(cmd->stdout, STDOUT);
				close(cmd->stdout);
			}
			if (next)
			{
				close(fds[STDIN]);
				close(fds[STDOUT]);
			}
			hook_child_signals();
			if (ft_execvpe(cmd->argv[0], cmd->argv, envp) == -1)
				return (perror("execute"), exit(EXIT_FAILURE), false);
		}
		if (prev_stdin != STDIN)
			close(prev_stdin);
		if (next)
		{
			prev_stdin = fds[STDIN];
			close(fds[STDOUT]);
			close(cmd->stdout);
		}
		current = next;
	}
	i = 0;
	while (i++ < commands->size)
		wait(0);
	return (true);
}
