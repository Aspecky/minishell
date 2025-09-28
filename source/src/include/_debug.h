/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _debug.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:43:36 by mtarrih           #+#    #+#             */
/*   Updated: 2025/09/15 21:24:39 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _DEBUG_H
# define _DEBUG_H

# include "SinglyLinkedList.h"

void	print_pipeline(const t_sllist *commands);
void	print_tokens(const t_sllist *tokens);

#endif
