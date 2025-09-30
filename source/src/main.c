/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:52:19 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/30 20:35:43 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SinglyLinkedList.h"
#include "defs.h"
#include "environ.h"
#include "execution.h"
#include "minishell.h"
#include "parsing.h"

#include "utils.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>

int			g_last_exit_status = 0;

static bool	init_main(t_main *main)
{
	main->input = 0;
	main->commands = sllist_new();
	main->env = environ_new();
	if (!main->commands || !main->env)
		return (free(main->commands), free(main->env), false);
	return (true);
}

static void	clean_main(t_main *main)
{
	environ_free(main->env);
	sllist_free(main->commands, cmd_free);
}

static int rl_signal_event_hook_handler(void)
{
	g_last_exit_status = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", false);
	rl_redisplay();
	return (0);
}

int	main(void)
{
	t_main	main;

	if (!init_shell_signals())
		return (print_error("sigaction", strerror(errno)), EXIT_FAILURE);
	rl_outstream = stderr;
	if (!init_main(&main))
		return (perror("main"), EXIT_FAILURE);
	rl_catch_signals = false;
	rl_signal_event_hook = rl_signal_event_hook_handler;
	while (true)
	{
		main.input = rl_gets(RL_PROMPT "> ");
		if (!main.input)
			break ;
		sllist_clear(main.commands, cmd_free);
		if (!parse(main.input, main.env->arr, main.commands))
			continue ;
		if (main.commands->size == 0)
			continue ;
		execute(main.commands, main.env);
	}
	clean_main(&main);
}
