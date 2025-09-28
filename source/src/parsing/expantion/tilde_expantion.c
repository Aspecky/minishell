/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expantion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:56:40 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/24 02:00:11 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"
#include "parsing.h"

char	*tilde_expantion(char *str, char *const envp[])
{
	char	*value;
	char	*ret;

	if (!(str[0] == '~' && (str[1] == '/' || !str[1])))
		return (ft_strdup(str));
	value = getenv_r("HOME", envp);
	if (!value)
		return (ft_strdup(str));
	if (!str[1])
		ret = ft_strdup(value);
	else
		ret = ft_strjoin(value, str + 1);
	return (ret);
}
