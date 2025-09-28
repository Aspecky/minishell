/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:30:47 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/26 20:25:41 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "parsing.h"
#include <ft_stdlib.h>
#include <stdlib.h>

t_cmd *cmd_new(char **argv, int argc, t_sllist *redirs)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->redirs = redirs;
	cmd->argv = argv;
	cmd->argc = argc;
	cmd->stdin_fd = STDIN;
	cmd->stdout_fd = STDOUT;
	return (cmd);
}

void cmd_free(void *ptr)
{
	t_cmd *cmd;
	int i;

	cmd = ptr;
	if (!cmd)
		return;
	i = 0;
	while (i < cmd->argc)
		free(cmd->argv[i++]);
	free(cmd->argv);
	sllist_free(cmd->redirs, redir_free);
	free(cmd);
}
