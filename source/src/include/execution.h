/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:49:13 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/25 22:18:28 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include "SinglyLinkedList.h"
#include "defs.h"
#include "environ.h"
#include <stdbool.h>
#include <unistd.h>

int ft_execvpe(const char *file, char *const argv[], char *const envp[]);
bool execute(t_sllist *commands, t_environ *env);

bool is_builtin(const char *str);
int echo_builtin(int ac, char *av[]);
int cd_builtin(int ac, char *av[], t_environ *env);
int pwd_builtin(void);
int exit_builtin(int ac, char *av[]);
int env_builtin(char *const envp[]);
int run_builtin(t_cmd *cmd, t_environ *env);

#endif
