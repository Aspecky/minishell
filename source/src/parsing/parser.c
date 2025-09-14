/* **************************************************************** while
   (**stream && !ft_isspace(**stream) && !is_special_char(**stream) && **stream
   != '\'' && **stream != '"')
			{
				if (total_len >= capacity - 1)
				{
					capacity *= 2;
					temp = realloc(result, capacity);
					if (!temp)
					{
						free(result);
						return (NULL);
					}
					result = temp;
				}
				result[total_len++] = **stream;
				(*stream)++;
			} */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:18:13 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/14 17:18:16 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_debug.h"
#include "ft_ctype.h"
#include "ft_string.h"
#include "parsing.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static char *extract_complete_word(char **stream)
{
	char *result = NULL;
	size_t total_len = 0;
	size_t capacity = 64;
	char *temp;

	result = malloc(capacity);
	if (!result)
		return (NULL);
	result[0] = '\0';

	while (**stream && !ft_isspace(**stream) && !is_special_char(**stream))
	{
		if (**stream == '\'' || **stream == '"')
		{
			// Extract quoted part
			char quote = **stream;
			(*stream)++; // Skip opening quote

			while (**stream && **stream != quote)
			{
				if (total_len >= capacity - 1)
				{
					capacity *= 2;
					temp = realloc(result, capacity);
					if (!temp)
					{
						free(result);
						return (NULL);
					}
					result = temp;
				}
				result[total_len++] = **stream;
				(*stream)++;
			}
			if (**stream == quote)
				(*stream)++; // Skip closing quote
		} else
		{
			// Extract unquoted part
			while (**stream && !ft_isspace(**stream) &&
				   !is_special_char(**stream) && **stream != '\'' &&
				   **stream != '"')
			{
				if (total_len >= capacity - 1)
				{
					capacity *= 2;
					temp = realloc(result, capacity);
					if (!temp)
					{
						free(result);
						return (NULL);
					}
					result = temp;
				}
				result[total_len++] = **stream;
				(*stream)++;
			}
		}
	}

	result[total_len] = '\0';
	return (result);
}

t_token *create_token(t_token_type type, char *value)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}

static size_t count_args_in_command(t_slnode *start, t_slnode *end)
{
	size_t count = 0;
	t_slnode *current = start;
	t_token *token;

	while (current && current != end)
	{
		token = (t_token *)current->data;
		if (token->type == TOKEN_WORD)
			count++;
		// Skip redirection tokens and their arguments
		else if (token->type == TOKEN_REDIRECT_IN ||
				 token->type == TOKEN_REDIRECT_OUT ||
				 token->type == TOKEN_REDIRECT_APPEND)
		{
			current = current->next; // Skip the redirection operator
			if (current && current != end)
				current = current->next; // Skip the filename
			continue;
		}
		current = current->next;
	}
	return (count);
}

static t_cmd *create_command_from_tokens(t_slnode *start, t_slnode *end)
{
	t_cmd *cmd;
	t_slnode *current = start;
	t_token *token;
	size_t argc = count_args_in_command(start, end);
	size_t i = 0;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);

	cmd->argv = malloc(sizeof(char *) * (argc + 1));
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}

	cmd->redirs = sllist_new();
	if (!cmd->redirs)
	{
		free(cmd->argv);
		free(cmd);
		return (NULL);
	}

	while (current && current != end)
	{
		token = (t_token *)current->data;
		if (token->type == TOKEN_WORD)
		{
			cmd->argv[i] = ft_strdup(token->value);
			if (!cmd->argv[i])
			{
				while (i > 0)
					free(cmd->argv[--i]);
				free(cmd->argv);
				sllist_free(cmd->redirs, free);
				free(cmd);
				return (NULL);
			}
			i++;
		}
		// Handle redirection tokens and their arguments
		else if (token->type == TOKEN_REDIRECT_IN ||
				 token->type == TOKEN_REDIRECT_OUT ||
				 token->type == TOKEN_REDIRECT_APPEND)
		{
			t_redir *redir = malloc(sizeof(t_redir));
			if (!redir)
			{
				while (i > 0)
					free(cmd->argv[--i]);
				free(cmd->argv);
				sllist_free(cmd->redirs, free);
				free(cmd);
				return (NULL);
			}

			// Set redirection type based on token type
			if (token->type == TOKEN_REDIRECT_IN)
				redir->type = REDIR_IN;
			else if (token->type == TOKEN_REDIRECT_OUT)
				redir->type = REDIR_OUT;
			else if (token->type == TOKEN_REDIRECT_APPEND)
				redir->type = REDIR_APPEND;

			redir->here_doc_read = -1; // Initialize to -1 for non-heredoc redirections

			current = current->next; // Move to the filename token
			if (current && current != end)
			{
				t_token *file_token = (t_token *)current->data;
				if (file_token->type == TOKEN_WORD)
				{
					redir->file_or_limiter = ft_strdup(file_token->value);
					if (!redir->file_or_limiter)
					{
						free(redir);
						while (i > 0)
							free(cmd->argv[--i]);
						free(cmd->argv);
						sllist_free(cmd->redirs, free);
						free(cmd);
						return (NULL);
					}
				}
				else
				{
					// Invalid redirection syntax - filename expected
					free(redir);
					while (i > 0)
						free(cmd->argv[--i]);
					free(cmd->argv);
					sllist_free(cmd->redirs, free);
					free(cmd);
					return (NULL);
				}
			}
			else
			{
				// Missing filename for redirection
				free(redir);
				while (i > 0)
					free(cmd->argv[--i]);
				free(cmd->argv);
				sllist_free(cmd->redirs, free);
				free(cmd);
				return (NULL);
			}

			if (!sllist_append(cmd->redirs, redir))
			{
				free(redir->file_or_limiter);
				free(redir);
				while (i > 0)
					free(cmd->argv[--i]);
				free(cmd->argv);
				sllist_free(cmd->redirs, free);
				free(cmd);
				return (NULL);
			}
		}
		current = current->next;
	}
	cmd->argv[i] = NULL;
	return (cmd);
}

t_sllist *group_into_commands(t_sllist *tokens)
{
	t_sllist *commands;
	t_slnode *current;
	t_slnode *cmd_start;
	t_token *token;

	commands = sllist_new();
	if (!commands)
		return (NULL);

	cmd_start = tokens->head;
	current = tokens->head;
	while (current)
	{
		token = current->data;

		if (token->type == TOKEN_PIPE)
		{
			// Create command from tokens between cmd_start and current
			t_cmd *cmd = create_command_from_tokens(cmd_start, current);
			if (!cmd)
			{
				free_pipeline_commands(commands);
				return (NULL);
			}
			if (!sllist_append(commands, cmd))
			{
				free(cmd->argv);
				free(cmd);
				free_pipeline_commands(commands);
				return (NULL);
			}
			cmd_start = current->next;
		}
		current = current->next;
	}

	// Handle the last command (after the last pipe or the only command)
	if (cmd_start)
	{
		t_cmd *cmd = create_command_from_tokens(cmd_start, NULL);
		if (!cmd)
		{
			free_pipeline_commands(commands);
			return (NULL);
		}
		if (!sllist_append(commands, cmd))
		{
			free(cmd->argv);
			free(cmd);
			free_pipeline_commands(commands);
			return (NULL);
		}
	}

	return (commands);
}

void free_tokens(t_sllist *tokens)
{
	t_slnode *current = tokens->head;
	t_token *token;

	while (current)
	{
		token = (t_token *)current->data;
		free(token->value);
		free(token);
		current = current->next;
	}
	sllist_free(tokens, NULL);
}

static void free_redir(void *data)
{
	t_redir *redir = (t_redir *)data;
	if (redir)
	{
		free(redir->file_or_limiter);
		free(redir);
	}
}

void free_pipeline_commands(t_sllist *commands)
{
	t_slnode *current;
	t_cmd *cmd;
	size_t j;

	if (!commands)
		return;

	current = commands->head;
	while (current)
	{
		cmd = (t_cmd *)current->data;
		if (cmd)
		{
			if (cmd->argv)
			{
				for (j = 0; cmd->argv[j]; j++)
					free(cmd->argv[j]);
				free(cmd->argv);
			}
			if (cmd->redirs)
				sllist_free(cmd->redirs, free_redir);
			free(cmd);
		}
		current = current->next;
	}
	sllist_free(commands, NULL);
}

void free_commands(t_cmd **commands, size_t count)
{
	size_t i, j;

	if (!commands)
		return;

	for (i = 0; i < count; i++)
	{
		if (commands[i])
		{
			if (commands[i]->argv)
			{
				for (j = 0; commands[i]->argv[j]; j++)
					free(commands[i]->argv[j]);
				free(commands[i]->argv);
			}
			if (commands[i]->redirs)
				sllist_free(commands[i]->redirs, free_redir);
			free(commands[i]);
		}
	}
	free(commands);
}

t_sllist *tokenize(char *stream)
{
	t_sllist *tokens;
	t_token *token;
	char *value;
	t_token_type type;

	tokens = sllist_new();
	if (!tokens)
		return (NULL);
	while (*stream)
	{
		type = TOKEN_EOF;

		// Skip whitespace
		if (ft_isspace(*stream))
			stream++;
		// Handle pipe
		else if (*stream == '|')
		{
			type = TOKEN_PIPE;
			value = ft_strdup("|");
			stream++;
		}
		// Handle redirections
		else if (*stream == '<')
		{
			type = TOKEN_REDIRECT_IN;
			value = ft_strdup("<");
			stream++;
		} else if (*stream == '>')
		{
			if (*(stream + 1) == '>')
			{
				type = TOKEN_REDIRECT_APPEND;
				value = ft_strdup(">>");
				stream += 2;
			} else
			{
				type = TOKEN_REDIRECT_OUT;
				value = ft_strdup(">");
				stream++;
			}
		}
		// Handle regular words (including mixed quoted/unquoted)
		else
		{
			type = TOKEN_WORD;
			value = extract_complete_word(&stream);
		}

		// Create token and add to list (only if we have a valid type)
		if (type != TOKEN_EOF)
		{
			if (!value)
			{
				sllist_free(tokens, free);
				return (NULL);
			}
			token = create_token(type, value);
			if (!token || !sllist_append(tokens, token))
			{
				if (token)
				{
					free(token->value);
					free(token);
				}
				sllist_free(tokens, free);
				return (NULL);
			}
		}
	}

	return (tokens);
}

t_sllist *parse(char *stream)
{
	t_sllist *tokens;
	t_sllist *commands;

	// Step 1: Tokenize the input
	tokens = tokenize(stream);
	if (!tokens)
		return (NULL);

	print_tokens(tokens);

	// Step 2: Group tokens into commands (split by pipes)
	commands = group_into_commands(tokens);
	if (!commands)
	{
		free_tokens(tokens);
		return (NULL);
	}

	// Step 3: Return the commands
	free_tokens(tokens);
	return (commands);
}
