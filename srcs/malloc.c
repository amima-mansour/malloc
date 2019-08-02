/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:47:23 by amansour          #+#    #+#             */
/*   Updated: 2019/08/02 10:38:47 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*malloc(size_t size)
{
	t_block		*b;
	size_t		new_size;

	pthread_mutex_lock(&g_mutex);
	new_size = ALIGN(size, 16);
    initialize_zone(new_size);
	if (!(b = find_or_create_block(g_zone.current, new_size)))
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	if (g_zone.type != LARGE && b->size >= new_size + B_SIZE)
		split_block(b, new_size);
    b->free = 0;
	pthread_mutex_unlock(&g_mutex);
	return ((char *)b + B_SIZE);
}
