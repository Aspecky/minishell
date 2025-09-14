/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:49 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/14 21:37:18 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "SinglyLinkedList.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum e_token_type : uint8_t {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_EOF
} t_token_type;

typedef enum e_redir_type : uint8_t {
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
} t_redir_type;

typedef struct s_token {
	t_token_type type;
	char *value;
} t_token;

typedef struct s_redir {
	t_redir_type type;
	char *file_or_limiter;
	int here_doc_read;
} t_redir;

typedef struct s_cmd {
	char **argv;
	t_sllist *redirs;
} t_cmd;

/* Main parsing function */
t_sllist *parse(char *stream);

/* Helper functions */
t_sllist *tokenize(char *stream);
int process_quotes(t_sllist *tokens);
t_sllist *group_into_commands(t_sllist *tokens);
void free_tokens(t_sllist *tokens);
void free_commands(t_cmd **commands, size_t count);
void free_pipeline_commands(t_sllist *commands);
t_token *create_token(t_token_type type, char *value);

#endif
