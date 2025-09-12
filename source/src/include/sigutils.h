/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigutils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 21:44:40 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/12 21:55:20 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGUTILS_H
#define SIGUTILS_H

#include <signal.h>

void init_sigaction(struct sigaction *act, void (*handler)(int));
void sigint_handler(int sig);

#endif
