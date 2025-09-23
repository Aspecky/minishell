/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:15:51 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/22 21:31:24 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"
#include "execution.h"
#include "minishell.h"
#include "signal_hooks.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

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

	// is_executing = true;
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
		pid = fork();
		if (pid == 0)
		{
			if (!setup_cmd_io(cmd))
				exit(EXIT_FAILURE);
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
			close(cmd->stdout_fd);
		}
		current = next;
	}

	size_t i;
	int wstatus;

	i = 0;
	while (i++ < commands->size)
	{
		if (wait(&wstatus) == -1)
		{
			printf("%i\n", errno);
			perror("wait");
			continue;
		}
		printf("'%s' wstatus: %i\n", cmd->argv[0], wstatus);
		if (WIFEXITED(wstatus))
		{
			// printf("\tWEXITSTATUS: %i\n", WEXITSTATUS(wstatus));
			g_last_exit_status = WEXITSTATUS(wstatus);
		} else if (WIFSIGNALED(wstatus))
		{
			// printf("\tWTERMSIG: %i\n", WTERMSIG(wstatus));
			g_last_exit_status = 128 + WTERMSIG(wstatus);
		}
	}
	// is_executing = false;
	// printf("last_exit_status: %i\n", g_last_exit_status);
	return (true);
}
