/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 22:35:16 by hasbayou          #+#    #+#             */
/*   Updated: 2025/10/01 15:43:11 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"
#include "execution.h"
#include "ft_stdio.h"
#include "minishell.h"
#include <unistd.h>

static int	dupminex(int oldfd, int minfd)
{
	int	fd;
	int	new_fd;

	fd = dup(oldfd);
	if (fd == -1)
		return (-1);
	if (fd > minfd)
		return (fd);
	new_fd = dupminex(oldfd, minfd);
	close(fd);
	return (new_fd);
}

void	exec_builtin(t_cmd *cmd, int fds[2], t_environ *env)
{
	int	saved_stdin;
	int	saved_stdout;

	if (!open_cmd_redirs(cmd))
		return ;
	saved_stdin = dupminex(STDIN, STDERR);
	saved_stdout = dupminex(STDOUT, STDERR);
	redirect_io(cmd, fds, false);
	g_last_exit_status = run_builtin(cmd, env);
	dup2(saved_stdin, STDIN);
	dup2(saved_stdout, STDOUT);
	close(saved_stdin);
	close(saved_stdout);
}
