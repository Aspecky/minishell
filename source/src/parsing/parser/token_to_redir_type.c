/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_redir_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 22:33:12 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/28 22:33:18 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_redir_type	token_to_redir_type(t_token_type token_type)
{
	if (token_type == TOKEN_REDIRECT_IN)
		return (REDIR_IN);
	else if (token_type == TOKEN_REDIRECT_OUT)
		return (REDIR_OUT);
	else if (token_type == TOKEN_REDIRECT_APPEND)
		return (REDIR_APPEND);
	else if (token_type == TOKEN_HEREDOC)
		return (REDIR_HEREDOC);
	return (REDIR_IN);
}
