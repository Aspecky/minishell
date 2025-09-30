/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:49:38 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/29 22:00:52 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# include "SinglyLinkedList.h"
# include "environ.h"
# include <stdbool.h>
# include <stdint.h>

typedef enum e_loop_control : uint8_t
{
	LOOP_NORMAL,
	LOOP_CONTINUE,
	LOOP_BREAK,
	LOOP_RETURN,
}					t_loop_control;

typedef enum e_redir_type : uint8_t
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}					t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file_or_delim;
	bool			was_quoted;
}					t_redir;

typedef struct s_cmd
{
	char			**argv;
	int				argc;
	int				stdin_fd;
	int				stdout_fd;
	int				heredoc_fd;
	t_sllist		*redirs;
}					t_cmd;

typedef struct s_main
{
	t_environ		*env;
	char			*input;
	t_sllist		*commands;
}					t_main;

#endif
