/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:22:28 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/15 21:28:13 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "SinglyLinkedList.h"
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
	int here_doc_read;
} t_redir;

typedef struct s_cmd {
	char **argv;
	size_t argc;
	t_sllist *redirs;
} t_cmd;

t_sllist *parse(char *stream);
t_sllist *tokens_to_commands(t_sllist *tokens);

t_cmd *cmd_new(char **argv, size_t argc, t_sllist *redirs);
void cmd_free(void *ptr);
t_redir *redir_new(t_redir_type type, char *file_or_delim);
void redir_free(void *ptr);

#endif
