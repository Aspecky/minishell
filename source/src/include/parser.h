/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:22:28 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/17 15:50:57 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "SinglyLinkedList.h"
#include <stdint.h>
#include "defs.h"

t_sllist *parse(char *stream);
t_sllist *tokens_to_commands(t_sllist *tokens);

t_cmd *cmd_new(char **argv, size_t argc, t_sllist *redirs);
void cmd_free(void *ptr);
t_redir *redir_new(t_redir_type type, char *file_or_delim);
void redir_free(void *ptr);

#endif
