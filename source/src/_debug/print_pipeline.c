/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:30:00 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/15 21:31:34 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_debug.h"
#include "parser.h"
#include <stdio.h>

void print_pipeline(const t_sllist *commands)
{
	t_slnode *current;
	t_cmd *cmd;
	size_t i;
	size_t j;

	if (!commands)
	{
		printf("Pipeline: NULL\n");
		return;
	}

	printf("Pipeline:\n");

	current = commands->head;
	i = 0;
	while (current)
	{
		printf("  Command %zu: ", i);

		cmd = (t_cmd *)current->data;
		if (!cmd)
		{
			printf("NULL\n");
		} else if (!cmd->argv || !cmd->argv[0])
		{
			printf("(empty command)\n");
		} else
		{
			printf("[");
			for (j = 0; cmd->argv[j]; j++)
			{
				if (j > 0)
					printf(", ");
				printf("\"%s\"", cmd->argv[j]);
			}
			printf("]\n");

			// Print redirections
			if (cmd->redirs && cmd->redirs->size > 0)
			{
				printf("    Redirections:\n");
				t_slnode *redir_node = cmd->redirs->head;
				size_t redir_idx = 0;
				while (redir_node)
				{
					t_redir *redir = (t_redir *)redir_node->data;
					if (redir)
					{
						printf("      [%zu] ", redir_idx);
						switch (redir->type)
						{
						case REDIR_IN:
							printf("< %s", redir->file_or_delim);
							break;
						case REDIR_OUT:
							printf("> %s", redir->file_or_delim);
							break;
						case REDIR_APPEND:
							printf(">> %s", redir->file_or_delim);
							break;
						case REDIR_HEREDOC:
							printf("<< %s", redir->file_or_delim);
							if (redir->here_doc_read != -1)
								printf(" (fd: %d)", redir->here_doc_read);
							break;
						}
						printf("\n");
					}
					redir_node = redir_node->next;
					redir_idx++;
				}
			}
		}

		current = current->next;
		i++;
	}
}
