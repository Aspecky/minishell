/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:14:12 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/25 22:18:32 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include <stdlib.h>
#include <unistd.h>

int echo_builtin(int ac, char *av[])
{
	bool print_nl;
	int i;

	print_nl = true;
	i = 1;
	while (i < ac && ft_strcmp(av[i], "-n") == 0)
	{
		print_nl = false;
		i++;
	}
	while (i < ac)
	{
		putstr(av[i]);
		if (i + 1 < ac)
			putstr(" ");
		i++;
	}
	if (print_nl)
		putstr("\n");
	return (EXIT_SUCCESS);
}
