/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 21:52:36 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/13 17:20:18 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>

void sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", false);
	rl_redisplay();
}

int hook_signals(void)
{
	struct sigaction sigint_act;
	struct sigaction sigquit_act;

	init_sigaction(&sigint_act, sigint_handler);
	init_sigaction(&sigquit_act, SIG_IGN);
	if (sigaction(SIGINT, &sigint_act, 0) == -1 ||
		sigaction(SIGQUIT, &sigquit_act, 0) == -1)
		return (-1);
	return (0);
}
