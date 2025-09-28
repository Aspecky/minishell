/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:30:58 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/26 20:59:15 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "minishell.h"
#include "utils.h"
#include <stdarg.h>

void	print_error(const char *cmd, const char *format, ...)
{
	va_list	args;

	dputstr(RL_PROMPT, STDERR);
	dputstr(": ", STDERR);
	dputstr(cmd, STDERR);
	dputstr(": ", STDERR);
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 's')
				dputstr(va_arg(args, char *), STDERR);
			else if (*format == 'i')
				dputlli(va_arg(args, int), STDERR);
		}
		else
			dputchar(*format, STDERR);
		format++;
	}
	va_end(args);
	dputstr("\n", STDERR);
}
