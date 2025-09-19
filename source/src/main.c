/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:52:19 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/19 02:43:37 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SinglyLinkedList.h"
#include "_debug.h"
#include "defs.h"
#include "environ.h"
#include "execution.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool init_main(t_main *main)
{
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
	if (hook_signals() == -1)
	{
		perror("sigaction");
		return (EXIT_FAILURE);
	}

	t_main main;
	char *line;

	if (!init_main(&main))
		return (perror("main"), EXIT_FAILURE);
	line = 0;
	while (true)
	{
		line = rl_gets(RL_PROMPT "> ");
		if (!line)
			break;
		parse(main.commands, line);
		if (main.commands->size == 0)
		{
			if (errno)
				perror("parser");
			continue;
		}

		// Print the parsed pipeline for debugging
		print_pipeline(main.commands);

		execute(main.commands, main.env->arr);

		// Free the pipeline resources
		sllist_clear(main.commands, cmd_free);
	}
	clean_main(&main);
	printf("exit\n");
}
