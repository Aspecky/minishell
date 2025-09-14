/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _debug.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:43:36 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/14 16:23:05 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _DEBUG_H
#define _DEBUG_H

#include "parsing.h"

void print_pipeline(const t_sllist *commands);
void print_tokens(const t_sllist *tokens);

#endif
