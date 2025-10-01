/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 22:40:19 by hasbayou          #+#    #+#             */
/*   Updated: 2025/10/01 15:43:34 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_stdio.h"

void	redirect_io(t_cmd *cmd, int fds[2], bool close_pipe)
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
