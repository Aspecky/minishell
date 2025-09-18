/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:52:19 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/18 16:34:39 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SinglyLinkedList.h"
#include "_debug.h"
#include "defs.h"
#include "execution.h"
#include "ft_string.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool init_main(t_main *main)
{
	main->env = envdup();
	if (!main->env)
		return (false);
	return (true);
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
		line = rl_gets(RL_PROMPT"> ");
		if (!line)
			break;
		main.commands = parse(line);
		if (!main.commands)
		{
			if (errno)
				perror("parser");
			continue;
		}

		// Print the parsed pipeline for debugging
		print_pipeline(main.commands);

		execute(main.commands, main.env);
		
		// Free the pipeline resources
		sllist_free(main.commands, cmd_free);
	}
	printf("exit\n");
}
