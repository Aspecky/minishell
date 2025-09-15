/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:12:17 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/15 21:28:02 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

t_redir *redir_new(t_redir_type type, char *file_or_delim)
{
	t_redir *redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (0);
	redir->type = type;
	redir->file_or_delim = file_or_delim;
	redir->here_doc_read = -1;
	return (redir);
}

void redir_free(void *ptr)
{
	t_redir *redir;
	
	redir = ptr;
	if (!redir)
		return ;
	free(redir->file_or_delim);
	free(redir);
}
