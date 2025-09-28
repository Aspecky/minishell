/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hooks.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:46:34 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/19 15:58:39 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HOOKS_H
# define SIGNAL_HOOKS_H

# include <signal.h>
# include <stdbool.h>

void	init_sigaction(struct sigaction *act, void (*handler)(int));
bool	hook_main_signals(void);
bool	hook_child_signals(void);

#endif
