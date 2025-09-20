/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:49:38 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/20 17:05:25 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
#define DEFS_H

#include "SinglyLinkedList.h"
#include "environ.h"
#include <stdbool.h>
#include <stdint.h>

typedef enum e_redir_type : uint8_t {
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
} t_redir_type;

typedef struct s_redir {
	t_redir_type type;
	char *file_or_delim;
	bool was_delim_quoted;
} t_redir;

typedef struct s_cmd {
	char **argv;
	size_t argc;
	int stdin;
	int stdout;
	t_sllist *redirs;
} t_cmd;

typedef struct s_main {
	t_environ *env;
	char *input;
	t_sllist *commands;
} t_main;

#endif
