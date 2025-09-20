/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_child_signals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:54:42 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/19 16:00:30 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_hooks.h"
#include <readline/readline.h>

bool hook_child_signals(void)
{
	struct sigaction act;

	rl_catch_signals = true;
	init_sigaction(&act, SIG_DFL);
	if (sigaction(SIGINT, &act, 0) == -1 || sigaction(SIGQUIT, &act, 0) == -1)
		return (false);
	return (true);
}
