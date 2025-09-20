/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_main_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:46:16 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/19 15:59:22 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_hooks.h"
#include <readline/readline.h>
#include <stdio.h>

void sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", false);
	rl_redisplay();
}

bool hook_main_signals(void)
{
	struct sigaction sigint_act;
	struct sigaction sigquit_act;

	init_sigaction(&sigint_act, sigint_handler);
	init_sigaction(&sigquit_act, SIG_IGN);
	if (sigaction(SIGINT, &sigint_act, 0) == -1 ||
		sigaction(SIGQUIT, &sigquit_act, 0) == -1)
		return (false);
	rl_catch_signals = false;
	return (true);
}
