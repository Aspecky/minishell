/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:49:57 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/29 01:27:40 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_stdio.h"
#include "utils.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	pwd_builtin(void)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (!pwd)
	{
		print_error("pwd", strerror(errno));
		return (EXIT_FAILURE);
	}
	if (putstr(pwd) == -1 || putstr("\n") == -1)
	{
		free(pwd);
		return (EXIT_FAILURE);
	}
	free(pwd);
	return (EXIT_SUCCESS);
}
