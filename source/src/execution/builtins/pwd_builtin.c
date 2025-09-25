/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:49:57 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/25 05:37:02 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int pwd_builtin(void)
{
	char *pwd;

	pwd = getcwd(0, 0);
	if (!pwd)
		return (EXIT_FAILURE); // TODO: print error
	printf("%s\n", pwd); // TODO: write error
	free(pwd);
	return (EXIT_SUCCESS);
}
