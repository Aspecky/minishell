/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_signals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:22:37 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/30 20:25:42 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static void	sigint_handler(int sig)
{
	(void)sig;
}

bool	init_shell_signals(void)
{
	struct sigaction	sigint_act;

	sigint_act.sa_handler = sigint_handler;
	sigemptyset(&sigint_act.sa_mask);
	sigint_act.sa_flags = 0;
	return (sigaction(SIGINT, &sigint_act, 0) != -1 && signal(SIGQUIT,
			SIG_IGN) != SIG_ERR && signal(SIGTERM, SIG_IGN) != SIG_ERR);
}
