/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 01:45:00 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/29 00:44:44 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>

static int	count_args_in_command(t_slnode *start, t_slnode *end)
{
	int			count;
	t_slnode	*current;
	t_token		*token;

	count = 0;
	current = start;
	while (current && current != end)
	{
		token = (t_token *)current->data;
		if (token->type == TOKEN_WORD)
			count++;
		else if (token->type == TOKEN_REDIRECT_IN
			|| token->type == TOKEN_REDIRECT_OUT
			|| token->type == TOKEN_REDIRECT_APPEND)
		{
			current = current->next;
			if (current && current != end)
				current = current->next;
			continue ;
		}
		current = current->next;
	}
	return (count);
}

static bool	handle_word_token(t_cmd *cmd, t_token *token)
{
	cmd->argv[cmd->argc] = ft_strdup(token->value);
	if (!cmd->argv[cmd->argc])
		return (false);
	cmd->argc++;
	return (true);
}

static bool	handle_redir_token(t_cmd *cmd, t_slnode **current)
{
	t_token	*token;
	t_redir	*redir;

	token = (*current)->data;
	redir = redir_new(0, 0);
	if (!redir)
		return (false);
	redir->type = token_to_redir_type(token->type);
	*current = (*current)->next;
	token = (*current)->data;
	redir->was_quoted = token->was_quoted;
	redir->file_or_delim = ft_strdup(token->value);
	if (!redir->file_or_delim)
		return (redir_free(redir), false);
	if (!sllist_append(cmd->redirs, redir))
		return (redir_free(redir), false);
	return (true);
}

static t_cmd	*new_command_from_tokens(t_slnode *start, t_slnode *end)
{
	t_slnode	*current;
	t_token		*token;
	t_cmd		*cmd;

	current = start;
	cmd = cmd_new(count_args_in_command(start, end));
	if (!cmd)
		return (NULL);
	while (current && current != end)
	{
		token = current->data;
		if (token->type == TOKEN_WORD)
		{
			if (!handle_word_token(cmd, token))
				return (cmd_free(cmd), NULL);
		}
		else if (is_redir_token(token))
			if (!handle_redir_token(cmd, &current))
				return (cmd_free(cmd), NULL);
		current = current->next;
	}
	cmd->argv[cmd->argc] = NULL;
	return (cmd);
}

bool	tokens_to_commands(t_sllist *pipeline, t_sllist *tokens)
{
	t_slnode	*current;
	t_slnode	*cmd_start;
	t_token		*token;
	t_cmd		*cmd;

	cmd_start = tokens->head;
	current = tokens->head;
	while (current)
	{
		token = current->data;
		if (token->type == TOKEN_PIPE || token->type == TOKEN_EOF)
		{
			cmd = new_command_from_tokens(cmd_start, current);
			if (!cmd)
				return (sllist_clear(pipeline, cmd_free), false);
			if (!sllist_append(pipeline, cmd))
				return (cmd_free(cmd), sllist_clear(pipeline, cmd_free), false);
			cmd_start = current->next;
		}
		current = current->next;
	}
	return (true);
}
