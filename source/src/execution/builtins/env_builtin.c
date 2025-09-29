/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 20:36:47 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/29 01:13:43 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_stdio.h"
#include "utils.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int	env_builtin(char *const envp[])
{
	while (*envp)
	{
		if (putstr(*envp) == -1 || putstr("\n") == -1)
		{
			print_error("env", strerror(errno));
			return (EXIT_FAILURE);
		}
		envp++;
	}
	return (EXIT_SUCCESS);
}
