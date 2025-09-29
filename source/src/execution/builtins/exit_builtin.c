/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:14:12 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/29 01:16:06 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_stdio.h"
#include "ft_stdlib.h"
#include "minishell.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

int	exit_builtin(int ac, char *av[])
{
	int	exit_code;
	int	status;

	if (ac == 1)
		exit(g_last_exit_status);
	if (ac > 2)
	{
		print_error("exit", "too many arguments");
		return (EXIT_FAILURE);
	}
	exit_code = atoi_s(av[1], &status);
	if (status != 0)
	{
		print_error("exit", "%s: numeric argument required", av[1]);
		exit(2);
	}
	exit(exit_code);
}
