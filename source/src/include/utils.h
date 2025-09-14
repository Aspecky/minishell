/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 21:44:40 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/14 15:44:07 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include <signal.h>

struct s_pipeline;

void init_sigaction(struct sigaction *act, void (*handler)(int));
char *rl_gets(const char *prompt);

#endif
