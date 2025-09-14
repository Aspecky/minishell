/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:52:19 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/14 21:54:00 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SinglyLinkedList.h"
#include "minishell.h"
#include "parsing.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "_debug.h"

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
			perror("parser");
			continue;
		}

		// Print the parsed pipeline for debugging
		print_pipeline(commands);

		// Free the pipeline resources
		free_pipeline_commands(commands);
	}
	printf("exit\n");
}
