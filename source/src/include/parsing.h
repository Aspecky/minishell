/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:36:24 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/28 20:36:27 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "SinglyLinkedList.h"
# include "Vector.h"
# include "defs.h"
# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>

/* External Definitions */
bool				parse(char *stream, char *const envp[], t_sllist *commands);
char				*param_expantion(char *str, char *const envp[]);
char				*expand_variable(char **str, char *const envp[],
						t_vector *vector);

/* Internal Definitions */
typedef enum e_token_type : uint8_t
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	bool			was_quoted;
}					t_token;

bool				validate_quotes_balance(const char *str);
bool				tokenize(char *stream, t_sllist *tokens);
bool				check_redirections(t_sllist *tokens);
bool				expand_words(t_sllist *tokens, char *const envp[]);
void				remove_quotes(t_sllist *tokens);
bool				tokens_to_commands(t_sllist *pipeline, t_sllist *tokens);
bool				process_heredocs(t_sllist *commands, char *const envp[]);
char				*tilde_expantion(char *str, char *const envp[]);

char				*heredoc_expantion(char *str, char *const envp[],
						ssize_t *len);
bool				validate_tokens(t_sllist *tokens);

int					is_word_separator(int c);
int					is_metacharacter(int c);
int					is_quote(int c);

// Objects
t_token				*token_new(t_token_type type, char *value);
t_redir				*redir_new(t_redir_type type, char *file_or_delim);
t_cmd				*cmd_new(char **argv, int argc, t_sllist *redirs);

void				token_free(void *data);
void				redir_free(void *ptr);
void				cmd_free(void *ptr);

#endif
