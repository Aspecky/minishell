/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:06:45 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/29 19:17:02 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_id(int *new_value)
{
	static int	value = 0;

	if (new_value)
		value = *new_value;
	return (value);
}
