/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:09:28 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/16 00:59:07 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdbool.h>
#include "lexer.h"

bool check_quotes_balance(const char *str);
bool check_redirections(t_sllist *tokens);

#endif
