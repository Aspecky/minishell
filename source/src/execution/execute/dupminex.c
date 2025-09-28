/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dupminex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:43:18 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/28 19:44:28 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int dupminex(int oldfd, int minfd)
{
	int fd;
	int new_fd;

	fd = dup(oldfd);
	if (fd == -1)
		return (-1);
	if (fd > minfd)
		return (fd);
	new_fd = dupminex(oldfd, minfd);
	close(fd);
	return (new_fd);
}
