/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_gets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:19:19 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/30 16:56:17 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

char	*rl_gets(const char *prompt)
{
	static char	*line = 0;

	if (line)
	{
		free(line);
		line = 0;
	}
	line = readline(prompt);
	if (line && *line)
		add_history(line);
	return (line);
}
