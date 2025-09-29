/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_heredoc_signals.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:47:13 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/29 19:35:38 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_hooks.h"
#include <readline/readline.h>

static void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
}

bool	hook_heredoc_signals(void)
{
	struct sigaction	sigint_act;

	init_sigaction(&sigint_act, sigint_handler);
	if (sigaction(SIGINT, &sigint_act, 0) == -1)
		return (false);
	rl_catch_signals = false;
	return (true);
}
