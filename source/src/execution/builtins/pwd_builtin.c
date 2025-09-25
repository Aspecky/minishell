/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:49:57 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/25 22:19:46 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_stdio.h"
#include <stdlib.h>
#include <unistd.h>

int pwd_builtin(void)
{
	char *pwd;

	pwd = getcwd(0, 0);
	if (!pwd)
		return (EXIT_FAILURE); // TODO: print error
	putstr(pwd);
	putstr("\n");
	free(pwd);
	return (EXIT_SUCCESS);
}
