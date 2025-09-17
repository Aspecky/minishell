/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 21:44:40 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/16 17:18:55 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include <signal.h>

void init_sigaction(struct sigaction *act, void (*handler)(int));
char *rl_gets(const char *prompt);
void env_free(char **env, size_t len);
char **envdup(void);

#endif
