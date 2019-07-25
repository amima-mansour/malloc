/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:47:37 by amansour          #+#    #+#             */
/*   Updated: 2019/07/23 15:41:21 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	*arrange_memory(t_block *block, size_t size)
{
	char		*new;
	enum e_type	type;

	pthread_mutex_lock(&g_mutex);
	type = g_zone.type;
	pthread_mutex_unlock(&g_mutex);
	new = (char *)malloc(size);
	pthread_mutex_lock(&g_mutex);
	ft_memmove(new, (char *)block + B_SIZE, block->size);
	g_zone.type = type;
	pthread_mutex_unlock(&g_mutex);
	clear_memory(block);
	return (new);
}

void	*realloc(void *ptr, size_t size)
{
	size_t		new_size;
	t_block		*b;

	if (!ptr)
		return (malloc(size));
	if (!(b = find_block(ptr)))
		return (NULL);
	new_size = ALIGN(size, ALIGNEMENT);
	if (b->size >= new_size)
		return (ptr);
	return (arrange_memory(b, new_size));
}
