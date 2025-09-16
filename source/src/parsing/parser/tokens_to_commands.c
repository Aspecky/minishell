/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 01:45:00 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/16 01:10:16 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

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

static t_cmd *new_command_from_tokens(t_slnode *start, t_slnode *end)
{
	t_slnode *current = start;
	t_token *token;
	t_cmd *cmd;
	t_redir *redir;

	cmd = cmd_new(0, 0, 0);
	if (!cmd)
		return (NULL);
	cmd->argv =
		malloc(sizeof(char *) * (count_args_in_command(start, end) + 1));
	cmd->redirs = sllist_new();
	if (!cmd->argv || !cmd->redirs)
		return (cmd_free(cmd), NULL);

	while (current && current != end)
	{
		token = (t_token *)current->data;
		if (token->type == TOKEN_WORD)
		{
			cmd->argv[cmd->argc] = ft_strdup(token->value);
			if (!cmd->argv[cmd->argc])
				return (cmd_free(cmd), NULL);
			cmd->argc++;
		}
		// Handle redirection tokens and their arguments
		else if (token->type == TOKEN_REDIRECT_IN ||
				 token->type == TOKEN_REDIRECT_OUT ||
				 token->type == TOKEN_REDIRECT_APPEND)
		{
			redir = redir_new(0, 0);
			if (!redir)
				return (cmd_free(cmd), NULL);

			// Set redirection type based on token type
			if (token->type == TOKEN_REDIRECT_IN)
				redir->type = REDIR_IN;
			else if (token->type == TOKEN_REDIRECT_OUT)
				redir->type = REDIR_OUT;
			else if (token->type == TOKEN_REDIRECT_APPEND)
				redir->type = REDIR_APPEND;

			current = current->next; // Move to the filename token
			t_token *file_token = (t_token *)current->data;
			redir->file_or_delim = ft_strdup(file_token->value);
			if (!redir->file_or_delim)
				return (redir_free(redir), cmd_free(cmd), NULL);

			if (!sllist_append(cmd->redirs, redir))
				return (redir_free(redir), cmd_free(cmd), NULL);
		}
		current = current->next;
	}
	cmd->argv[cmd->argc] = NULL;
	return (cmd);
}

t_sllist *tokens_to_commands(t_sllist *tokens)
{
	t_sllist *pipeline;
	t_slnode *current;
	t_slnode *cmd_start;
	t_token *token;
	t_cmd *cmd;

	pipeline = sllist_new();
	if (!pipeline)
		return (NULL);

	cmd_start = tokens->head;
	current = tokens->head;
	while (current)
	{
		token = current->data;

		if (token->type == TOKEN_PIPE || token->type == TOKEN_EOF)
		{
			// Create command from tokens between cmd_start and current
			cmd = new_command_from_tokens(cmd_start, current);
			if (!cmd)
				return (sllist_free(pipeline, cmd_free), NULL);
			if (!sllist_append(pipeline, cmd))
				return (cmd_free(cmd), sllist_free(pipeline, cmd_free), NULL);
			cmd_start = current->next;
		}
		current = current->next;
	}
	return (pipeline);
}
