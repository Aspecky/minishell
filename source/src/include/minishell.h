/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:13:35 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/24 18:54:45 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define RL_PROMPT "uwushell"

#include "defs.h"
#include <stdbool.h>

extern bool is_executing;
extern int g_last_exit_status;

void terminate(t_main *main);

#endif
