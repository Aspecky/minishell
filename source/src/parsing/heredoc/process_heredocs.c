/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:26:29 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/29 19:35:31 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"
#include "ft_string.h"
#include "minishell.h"
#include "parsing.h"
#include "signal_hooks.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static bool	post_loop(t_pch_vars *v, t_cmd *cmd)
{
	(free(v->lninfo.line), free(v->lninfo.store));
	if (v->len == -1)
	{
		if (cmd->stdin_fd != STDIN)
			close(cmd->stdin_fd);
		return (close(v->fds[0]), close(v->fds[1]), false);
	}
	close(v->fds[STDOUT]);
	if (cmd->stdin_fd != STDIN)
		close(cmd->stdin_fd);
	cmd->stdin_fd = v->fds[STDIN];
	return (true);
}

static bool	on_error(int fds[2], void *p1, void *p2)
{
	close(fds[0]);
	close(fds[1]);
	free(p1);
	free(p2);
	return (false);
}

static bool	is_delimiter_reached(t_pch_vars *v, t_redir *redir)
{
	return ((size_t)v->len - 1 == v->delim_len && ft_strncmp(v->lninfo.line,
			redir->file_or_delim, v->delim_len) == 0);
}

static bool	process_cmd_heredoc(t_cmd *cmd, t_redir *redir, char *const envp[])
{
	t_pch_vars	v;

	if (pipe(v.fds) == -1)
		return (false);
	v.lninfo = (t_lninfo){0, 0, 0, 0};
	v.delim_len = ft_strlen(redir->file_or_delim);
	while (true)
	{
		(dputstr("> ", STDOUT), v.len = dgetline(STDIN, &v.lninfo));
		if (v.len <= 0 || is_delimiter_reached(&v, redir))
			break ;
		v.line = v.lninfo.line;
		if (!redir->was_quoted)
		{
			v.line = heredoc_expantion(v.lninfo.line, envp, &v.len);
			if (!v.line)
				return (on_error(v.fds, v.lninfo.line, v.lninfo.store));
		}
		if (write(v.fds[STDOUT], v.line, (size_t)v.len) == -1)
			return (on_error(v.fds, v.line, v.lninfo.store));
		if (!redir->was_quoted)
			free(v.line);
	}
	return (post_loop(&v, cmd));
}

bool	process_heredocs(t_sllist *commands, char *const envp[])
{
	t_slnode	*cmd_node;
	t_slnode	*redir_node;
	t_cmd		*cmd;
	t_redir		*redir;

	hook_heredoc_signals();
	cmd_node = commands->head;
	while (cmd_node)
	{
		cmd = cmd_node->data;
		redir_node = cmd->redirs->head;
		while (redir_node)
		{
			redir = redir_node->data;
			if (redir->type == REDIR_HEREDOC)
				if (!process_cmd_heredoc(cmd, redir, envp))
					return (hook_main_signals(), false);
			redir_node = redir_node->next;
		}
		cmd_node = cmd_node->next;
	}
	hook_main_signals();
	return (true);
}
