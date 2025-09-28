/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 21:44:40 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/28 16:11:50 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdbool.h>

char *rl_gets(const char *prompt);
void print_error(const char *cmd, const char *format, ...);
bool is_executing(bool *new_value);

#endif
