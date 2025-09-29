/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:13:35 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/29 17:51:22 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RL_PROMPT "uwushell"

# include "defs.h"
# include <stdbool.h>

extern int	g_last_exit_status;
bool	is_executing(bool *new_value);
int		heredoc_id(int *new_value);

#endif
