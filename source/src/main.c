/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:52:19 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/12 22:16:24 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <readline/readline.h>

int main(void)
{
	if (hook_signals() == -1)
	{
		perror("sigaction");
		return (EXIT_FAILURE);
	}

	char *line;

	line = 0;
	while (true)
	{
		(free(line), line = 0);
		line = readline("minishell> ");
		if (!line)
			break;
		printf("'%s'\n", line);
	}
	free(line);
	printf("exit\n");
}
