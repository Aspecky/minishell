/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:08:28 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/15 21:27:02 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include "SinglyLinkedList.h"
#include <stdint.h>

typedef enum e_token_type : uint8_t {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_EOF
} t_token_type;

typedef struct s_token {
	t_token_type type;
	char *value;
} t_token;

t_sllist *tokenize(char *stream);

t_token *token_new(t_token_type type, char *value);
void token_free(void *data);

#endif
