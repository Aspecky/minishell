/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 18:52:38 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/25 18:40:01 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"
#include "minishell.h"
#include <stdlib.h>

void terminate(t_main *main)
{
	environ_free(main->env);
	free(main->commands);
	exit(g_last_exit_status);
}
