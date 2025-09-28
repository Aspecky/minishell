/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 23:54:56 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/26 02:56:22 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <stdlib.h>

int unset_builtin(int ac, char *av[], t_environ *env)
{
	int i;
	int status;

	if (ac == 1)
		return (EXIT_SUCCESS);
	
	status = EXIT_SUCCESS;
	i = 1;
	while (i < ac)
	{
		if (!environ_unset(env, av[i]))
			status = EXIT_FAILURE;
		i++;
	}
	
	return (status);
}
