/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:14:12 by hasbayou          #+#    #+#             */
/*   Updated: 2025/10/01 15:42:51 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "utils.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	on_write_error(void)
{
	print_error("echo", "write error: %s", strerror(errno));
	return (EXIT_FAILURE);
}

int	echo_builtin(int ac, char *av[])
{
	bool	print_nl;
	int		i;

	print_nl = true;
	i = 1;
	while (i < ac && ft_strcmp(av[i], "-n") == 0)
	{
		print_nl = false;
		i++;
	}
	while (i < ac)
	{
		if (putstr(av[i]) == -1)
			return (on_write_error());
		if (i + 1 < ac)
			if (putstr(" ") == -1)
				return (on_write_error());
		i++;
	}
	if (print_nl)
		if (putstr("\n") == -1)
			return (on_write_error());
	return (EXIT_SUCCESS);
}
