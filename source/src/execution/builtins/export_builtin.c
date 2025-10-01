/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:55:43 by hasbayou          #+#    #+#             */
/*   Updated: 2025/10/01 15:42:40 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "execution.h"
#include "ft_ctype.h"
#include "ft_stdio.h"
#include "utils.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char	*trim_value(char *value)
{
	size_t	i;
	size_t	j;

	while (ft_isspace(*value))
		value++;
	i = 0;
	j = 0;
	while (value[i])
	{
		if (ft_isspace(value[i]))
		{
			j++;
			i++;
			while (ft_isspace(value[i]))
				i++;
		}
		else
			value[j++] = value[i++];
	}
	if (ft_isspace(value[j]))
		j--;
	value[j] = 0;
	return (value);
}

static bool	split_to_name_value(char *str, char **name, char **value)
{
	char	*equal_ptr;
	size_t	i;

	equal_ptr = 0;
	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
		i++;
	if (!str[i])
		return (true);
	if (str[i] == '=')
		equal_ptr = str + i;
	if (!equal_ptr)
		return (false);
	*equal_ptr = 0;
	*name = str;
	*value = equal_ptr + 1;
	return (true);
}

static bool	print_exports(t_environ *env)
{
	char	**ptr;

	ptr = env->arr;
	while (*ptr)
	{
		if (putstr("declare -x ") == -1
			|| putstr(*ptr) == -1 || putstr("\n") == -1)
			return (false);
		ptr++;
	}
	return (true);
}

static int	do_export(int ac, char *av[], t_environ *env)
{
	int		i;
	char	*name;
	char	*value;

	i = 1;
	while (i < ac)
	{
		if (split_to_name_value(av[i], &name, &value))
		{
			if (!environ_set(env, name, trim_value(value)))
			{
				print_error("export", "environ_set: %s", strerror(errno));
				return (EXIT_FAILURE);
			}
		}
		else
		{
			print_error("export", "`%s': not a valid identifier", av[i]);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	export_builtin(int ac, char *av[], t_environ *env)
{
	if (ac == 1)
	{
		if (!print_exports(env))
		{
			print_error("export", "%s", strerror(errno));
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	else
		return (do_export(ac, av, env));
}
