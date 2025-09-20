/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:52:19 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/20 17:06:06 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SinglyLinkedList.h"
#include "_debug.h"
#include "defs.h"
#include "environ.h"
#include "execution.h"
#include "minishell.h"
#include "parser.h"
#include "signal_hooks.h"
#include "utils.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool init_main(t_main *main)
{
	main->input = 0;
	main->commands = sllist_new();
	main->env = environ_new();
	if (!main->commands || !main->env)
		return (free(main->commands), free(main->env), false);
	return (true);
}

void clean_main(t_main *main)
{
	environ_free(main->env);
	free(main->commands);
}

// TODO: bash prompts in stderr not stdout
int main(void)
{
	if (!hook_main_signals())
	{
		perror("sigaction");
		return (EXIT_FAILURE);
	}

	t_main main;

	if (!init_main(&main))
		return (perror("main"), EXIT_FAILURE);
	while (true)
	{
		main.input = rl_gets(RL_PROMPT "> ");
		if (!main.input)
			break;
		parse(main.input, main.env->arr, main.commands);
		if (main.commands->size == 0)
		{
			if (errno)
				perror("parser");
			continue;
		}

		// print_pipeline(main.commands);

		execute(main.commands, main.env->arr);

		sllist_clear(main.commands, cmd_free);
	}
	clean_main(&main);
	printf("exit\n");
}
