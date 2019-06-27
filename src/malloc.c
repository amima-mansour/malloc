/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:47:23 by amansour          #+#    #+#             */
/*   Updated: 2019/06/27 17:26:13 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_zone				g_zone = {TINY, NULL, NULL, NULL, NULL};
pthread_mutex_t		g_mutex = PTHREAD_MUTEX_INITIALIZER;

void				*malloc(size_t size)
{
	t_block		*bp;
	size_t		new_size;

	if ((int)size < 0)
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	new_size = ALIGN(size, ALIGNEMENT);
	initialize_zone(new_size);
	bp = find_or_create_block(new_size, g_zone.current);
	pthread_mutex_unlock(&g_mutex);
	return ((char*)bp + B_SIZE);
}
