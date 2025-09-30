/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:49:13 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/30 22:48:46 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "SinglyLinkedList.h"
# include "defs.h"
# include "environ.h"
# include <errno.h>
# include <signal.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>

typedef struct s_execute_vars
{
	t_slnode	*current;
	t_slnode	*next;
	t_cmd		*cmd;
	int			fds[2];
	pid_t		last_pid;
	int			prev_stdin;
}				t_execute_vars;

void			execute(t_sllist *commands, t_environ *env);
bool			exec_fork(t_execute_vars *vars, t_environ *env);
void			exec_builtin(t_cmd *cmd, int fds[2], t_environ *env);
void			redirect_io(t_cmd *cmd, int fds[2], bool close_pipe);

bool			open_cmd_redirs(t_cmd *cmd);
int				ft_execvpe(const char *file, char *const argv[],
					char *const envp[]);

bool			is_builtin(const char *str);
int				echo_builtin(int ac, char *av[]);
int				cd_builtin(int ac, char *av[], t_environ *env);
int				pwd_builtin(void);
int				exit_builtin(int ac, char *av[]);
int				env_builtin(char *const envp[]);
int				unset_builtin(int ac, char *av[], t_environ *env);
int				export_builtin(int ac, char *av[], t_environ *env);
int				run_builtin(t_cmd *cmd, t_environ *env);

typedef struct s_deip_vars
{
	const char	*current_dir;
	const char	*next_dir;
	char		*full_path;
	size_t		dir_len;
	bool		got_eaccess;
}				t_deip_vars;

#endif
