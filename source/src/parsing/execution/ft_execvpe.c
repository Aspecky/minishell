/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvpe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:48:53 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/17 01:50:55 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>

// https://github.com/bminor/glibc/blob/master/posix/execvpe.c
int ft_execvpe(const char *file, char *const argv[], char *const envp[])
{
	char *path;
	char *p;
	char *subp;
	char *pend;
	size_t file_len;
	size_t path_len;
	size_t size;
	bool got_eaccess;

	if (ft_strchr(file, '/'))
		return (execve(file, argv, envp), -1);
	path = getenv_r("PATH", envp);
	// TODO: if path is not found, return confstr(_CS_PATH)
	if (!path)
		return (-1);
	file_len = ft_strlen(file);
	p = path;
	pend = 0;
	got_eaccess = false;
	while (true)
	{
		free(pend);
		subp = ft_strchrnul(p, ':');
		path_len = subp - p;
		size = path_len + file_len + 2;
		pend = malloc(sizeof(char) * size);
		if (!pend)
			return (-1);
		ft_memcpy(pend, p, path_len);
		*(pend + path_len) = '/';
		ft_memcpy(pend + path_len + 1, file, file_len);
		pend[size - 1] = 0;
		execve(pend, argv, envp);
		if (errno == EACCES)
			got_eaccess = true;
		else if (errno != ENOENT && errno != ESTALE && errno != ENOTDIR &&
				 errno != ENODEV && errno != ETIMEDOUT)
			return (free(pend), -1);
		if (!*subp++)
			break;
		p = subp;
	}
	free(pend);
	if (got_eaccess)
		errno = EACCES;
	return (-1);
}
