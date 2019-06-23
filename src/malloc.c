/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:47:23 by amansour          #+#    #+#             */
/*   Updated: 2019/05/29 13:47:26 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void    *malloc(size_t size)
{
	t_block	    *bp;
	size_t		new_size;

	if ((int)size < 0)
		return (NULL);
	pthread_mutex_lock(&g_mutex);
    initialize_zone(ALIGN(size, ALIGNEMENT));
	new_size = ALIGN(size, ALIGNEMENT);
    bp = find_or_create_block(new_size);
	pthread_mutex_unlock(&g_mutex);
	return bp;
}