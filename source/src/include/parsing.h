#ifndef PARSING_H
#define PARSING_H

#include "SinglyLinkedList.h"
#include "defs.h"
#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

/* External Definitions */
void parse(char *stream, char *const envp[], t_sllist *commands);
char *param_expantion(char *str, char *const envp[]);

/* Internal Definitions */
typedef enum e_token_type : uint8_t {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
} t_token_type;

typedef struct s_token {
	t_token_type type;
	char *value;
	bool was_quoted;
} t_token;

bool check_quotes_balance(const char *str);
t_sllist *tokenize(char *stream);
bool check_redirections(t_sllist *tokens);
bool expand_words(t_sllist *tokens, char *const envp[]);
void remove_quotes(t_sllist *tokens);
void tokens_to_commands(t_sllist *pipeline, t_sllist *tokens);
bool process_heredocs(t_sllist *commands, char *const envp[]);
char *tilde_expantion(char *str, char *const envp[]);

char *heredoc_expantion(char *str, char *const envp[], ssize_t *len);

int is_word_separator(int c);
int is_metacharacter(int c);
int is_quote(int c);

// Objects
t_token *token_new(t_token_type type, char *value);
t_redir *redir_new(t_redir_type type, char *file_or_delim);
t_cmd *cmd_new(char **argv, size_t argc, t_sllist *redirs);

void token_free(void *data);
void redir_free(void *ptr);
void cmd_free(void *ptr);

#endif
