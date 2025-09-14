/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sigaction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 21:47:47 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/13 17:20:53 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void init_sigaction(struct sigaction *act, void (*handler)(int))
{
	act->sa_handler = handler;
	sigemptyset(&act->sa_mask);
	act->sa_flags = 0;
	act->sa_restorer = 0;	
}
