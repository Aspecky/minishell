/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 02:06:33 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/19 02:09:43 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include <stdlib.h>

void environ_free(t_environ *env)
{
	if (!env)
		return ;
	sllist_free(env->list, free);
	free(env->arr);
	free(env);
}
