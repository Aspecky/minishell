/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:52:19 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/16 00:32:35 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SinglyLinkedList.h"
#include "_debug.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
	if (hook_signals() == -1)
	{
		perror("sigaction");
		return (EXIT_FAILURE);
	}

	t_sllist *commands;
	char *line;

	line = 0;
	while (true)
	{
		line = rl_gets("minishell> ");
		if (!line)
			break;
		commands = parse(line);
		if (!commands)
		{
			if (errno != EXIT_SUCCESS)
				perror("parser");
			continue;
		}

		// Print the parsed pipeline for debugging
		print_pipeline(commands);

		// Free the pipeline resources
		sllist_free(commands, cmd_free);
	}
	printf("exit\n");
}
