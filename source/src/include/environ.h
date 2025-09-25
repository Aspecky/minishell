/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 01:53:42 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/25 17:16:22 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
#define ENVIRON_H

#include "SinglyLinkedList.h"
#include <stdbool.h>

typedef struct s_environ {
	t_sllist *list;
	char **arr;
} t_environ;

t_environ *environ_new(void);
void environ_free(t_environ *env);
bool environ_set(t_environ *env, const char *name, const char *value);

char **environ_list_to_envp(t_sllist *list);

#endif
