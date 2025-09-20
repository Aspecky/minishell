/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:30:47 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/20 18:00:13 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"
#include <ft_stdlib.h>
#include <stdlib.h>

t_cmd *cmd_new(char **argv, size_t argc, t_sllist *redirs)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->redirs = redirs;
	cmd->argv = argv;
	cmd->argc = argc;
	cmd->stdin = STDIN;
	cmd->stdout = STDOUT;
	return (cmd);
}

void cmd_free(void *ptr)
{
	t_cmd *cmd;
	size_t i;

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
