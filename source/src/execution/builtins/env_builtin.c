/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 20:36:47 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/25 22:20:29 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_stdio.h"
#include <stdlib.h>

int env_builtin(char *const envp[])
{
	while (*envp)
	{
		putstr(*envp);
		putstr("\n");
		envp++;
	}
	return (EXIT_SUCCESS);
}
