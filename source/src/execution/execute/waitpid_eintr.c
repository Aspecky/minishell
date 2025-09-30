/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid_eintr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:03:07 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/30 19:04:13 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <sys/wait.h>

int waitpid_eintr(pid_t pid, int *wstatus, int options)
{
	int ret;

	ret = waitpid(pid, wstatus, options);
	if (ret == -1 && errno == EINTR)
		return (waitpid_eintr(pid, wstatus, options));
	return (ret);
}
