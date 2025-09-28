/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_child_signals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:54:42 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/22 21:28:29 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_hooks.h"
#include <readline/readline.h>

bool	hook_child_signals(void)
{
	rl_catch_signals = true;
	if (signal(SIGINT, SIG_DFL) == SIG_ERR || signal(SIGQUIT,
			SIG_DFL) == SIG_ERR)
		return (false);
	return (true);
}
