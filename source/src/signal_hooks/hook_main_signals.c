/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_main_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:46:16 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/28 15:54:17 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signal_hooks.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>

#include <unistd.h>

void sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	if (!is_executing)
	{
		g_last_exit_status = 1;
		rl_on_new_line();
	}
	rl_replace_line("", false);
	rl_redisplay();
}

bool hook_main_signals(void)
{
	struct sigaction sigint_act;

	init_sigaction(&sigint_act, sigint_handler);
	sigint_act.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sigint_act, 0) == -1 ||
		signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (false);
	rl_catch_signals = false;
	return (true);
}
