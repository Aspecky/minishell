/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvpe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:48:53 by hasbayou          #+#    #+#             */
/*   Updated: 2025/10/01 15:43:42 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>

static char	*get_search_path(char *const envp[], bool *malloced)
{
	char	*path;

	*malloced = false;
	path = getenv_r("PATH", envp);
	if (!path || !*path)
	{
		path = getcwd(0, 0);
		if (!path)
			return (NULL);
		*malloced = true;
	}
	return (path);
}

static char	*build_full_path(const char *dir, size_t dir_len, const char *file)
{
	size_t	file_len;
	size_t	total_size;
	char	*full_path;

	file_len = ft_strlen(file);
	total_size = dir_len + file_len + 2;
	full_path = malloc(sizeof(char) * total_size);
	if (!full_path)
		return (NULL);
	ft_memcpy(full_path, dir, dir_len);
	*(full_path + dir_len) = '/';
	ft_memcpy(full_path + dir_len + 1, file, file_len);
	full_path[total_size - 1] = '\0';
	return (full_path);
}

static bool	is_recoverable_error(void)
{
	return (errno == ENOENT || errno == ESTALE || errno == ENOTDIR
		|| errno == ENODEV || errno == ETIMEDOUT);
}

static int	do_execve_in_path(const char *file, char *const argv[],
		char *const envp[], const char *search_path)
{
	t_deip_vars	vars;

	vars = (t_deip_vars){.current_dir = search_path, .got_eaccess = false};
	while (true)
	{
		vars.next_dir = ft_strchrnul(vars.current_dir, ':');
		vars.dir_len = vars.next_dir - vars.current_dir;
		vars.full_path = build_full_path(vars.current_dir, vars.dir_len, file);
		if (!vars.full_path)
			return (-1);
		execve(vars.full_path, argv, envp);
		if (errno == EACCES)
			vars.got_eaccess = true;
		else if (!is_recoverable_error())
			return (free(vars.full_path), -1);
		free(vars.full_path);
		if (!*vars.next_dir++)
			break ;
		vars.current_dir = vars.next_dir;
	}
	if (vars.got_eaccess)
		errno = EACCES;
	return (-1);
}

// https://github.com/bminor/glibc/blob/master/posix/execvpe.c
int	ft_execvpe(const char *file, char *const argv[], char *const envp[])
{
	char	*search_path;
	int		result;
	bool	was_path_malloced;

	if (ft_strchr(file, '/'))
		return (execve(file, argv, envp), -1);
	search_path = get_search_path(envp, &was_path_malloced);
	if (!search_path)
		return (-1);
	result = do_execve_in_path(file, argv, envp, search_path);
	if (was_path_malloced)
		free(search_path);
	return (result);
}
