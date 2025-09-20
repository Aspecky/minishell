/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:49:13 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/20 16:01:27 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include "SinglyLinkedList.h"
#include <unistd.h>
#include <stdbool.h>
#include "ft_stdio.h"

int ft_execvpe(const char *file, char *const argv[], char *const envp[]);
bool execute(t_sllist *commands, char *const envp[]);
bool process_heredocs(t_sllist *commands);

#endif
