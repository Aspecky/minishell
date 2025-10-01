/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:49:57 by hasbayou          #+#    #+#             */
/*   Updated: 2025/10/01 15:42:32 by hasbayou         ###   ########.fr       */
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
