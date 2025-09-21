/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:26:29 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/21 23:17:07 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool process_cmd_heredoc(t_cmd *cmd, t_redir *redir, char *const envp[])
{
	int fd[2];
	t_lninfo lninfo;
	ssize_t len;
	size_t delim_len;
	char *line;

	if (pipe(fd) == -1)
		return (false);
	lninfo = (t_lninfo){0, 0, 0, 0};
	delim_len = ft_strlen(redir->file_or_delim);
	while (true)
	{
		dputstr("> ", STDOUT);
		len = dgetline(STDIN, &lninfo);
		if (len <= 0 ||
			((size_t)len - 1 == delim_len &&
			 ft_strncmp(lninfo.line, redir->file_or_delim, delim_len) == 0))
			break;
		line = lninfo.line;
		if (!redir->was_quoted)
		{
			// TODO: Cleanup on error
			line = expand_word(lninfo.line, envp, &len);
			if (!line)
				return (false);
		}
		if (write(fd[STDOUT], line, (size_t)len) == -1)
			return (close(fd[0]), close(fd[1]), free(line),
					free(lninfo.store), false);
		if (!redir->was_quoted)
			free(line);
	}
	(free(lninfo.line), free(lninfo.store));
	close(fd[STDOUT]);
	if (cmd->stdin_fd != STDIN)
		close(cmd->stdin_fd);
	cmd->stdin_fd = fd[STDIN];
	return (true);
}

bool process_heredocs(t_sllist *commands, char *const envp[])
{
	t_slnode *cmd_node;
	t_slnode *redir_node;
	t_cmd *cmd;
	t_redir *redir;

	cmd_node = commands->head;
	while (cmd_node)
	{
		cmd = cmd_node->data;
		redir_node = cmd->redirs->head;
		while (redir_node)
		{
			redir = redir_node->data;
			if (redir->type == REDIR_HEREDOC)
			{
				process_cmd_heredoc(cmd, redir, envp);
			}
			redir_node = redir_node->next;
		}
		cmd_node = cmd_node->next;
	}
	return (true);
}
