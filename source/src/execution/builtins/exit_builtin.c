/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:14:12 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/25 18:31:08 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_stdlib.h"
#include "minishell.h"
#include "ft_stdio.h"
#include <stdlib.h>
#include <unistd.h>

int exit_builtin(int ac, char *av[])
{
	int exit_code;
	int status;
	
	// No arguments - exit with last status
	if (ac == 1)
		exit(g_last_exit_status);
	
	// Too many arguments - print error but don't exit
	if (ac > 2)
	{
		dputstr("exit: too many arguments\n", STDERR);
		return (EXIT_FAILURE);
	}
	
	// One argument - parse as exit code
	exit_code = atoi_s(av[1], &status);
	
	// Invalid numeric argument
	if (status != 0)
	{
		dputstr("exit: ", STDERR);
		dputstr(av[1], STDERR);
		dputstr(": numeric argument required\n", STDERR);
		exit(2);
	}
	
	// Valid argument - exit with the parsed code (modulo 256)
	exit((unsigned char)exit_code);
}
