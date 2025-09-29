/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_executing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:09:44 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/29 17:05:39 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_executing(bool *new_value)
{
	static bool	value = 0;

	if (new_value)
		value = *new_value;
	return (value);
}
