/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_cmd_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 00:32:19 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/29 22:30:29 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"
#include "execution.h"
#include "ft_stdio.h"
#include "utils.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>

static bool redir_in(t_cmd *cmd, t_redir *redir)
{
	if (cmd->stdin_fd != cmd->heredoc_fd && cmd->stdin_fd != STDIN)
		close(cmd->stdin_fd);
	cmd->stdin_fd = open(redir->file_or_delim, O_RDONLY);
	return (cmd->stdin_fd != -1);
}

static bool redir_out(t_cmd *cmd, t_redir *redir)
{
	if (cmd->stdout_fd != STDOUT)
		close(cmd->stdout_fd);
	cmd->stdout_fd =
		open(redir->file_or_delim, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (cmd->stdout_fd != -1);
}

static bool redir_append(t_cmd *cmd, t_redir *redir)
{
	if (cmd->stdout_fd != STDOUT)
		close(cmd->stdout_fd);
	cmd->stdout_fd =
		open(redir->file_or_delim, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (cmd->stdout_fd != -1);
}

static bool on_redir(t_cmd *cmd, t_redir *redir)
{
	bool status;

	status = true;
	if (redir->type == REDIR_IN)
		status = redir_in(cmd, redir);
	else if (redir->type == REDIR_OUT)
		status = redir_out(cmd, redir);
	else if (redir->type == REDIR_APPEND)
		status = redir_append(cmd, redir);
	else if (redir->type == REDIR_HEREDOC)
		cmd->stdin_fd = cmd->heredoc_fd;
	if (!status)
		print_error(redir->file_or_delim, strerror(errno));
	return (status);
}

bool open_cmd_redirs(t_cmd *cmd)
{
	t_redir *redir;
	t_slnode *node;

	node = cmd->redirs->head;
	while (node)
	{
		redir = node->data;
		if (!on_redir(cmd, redir))
			return (false);
		node = node->next;
	}
	return (true);
}
