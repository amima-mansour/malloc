/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:47:37 by amansour          #+#    #+#             */
/*   Updated: 2019/07/31 10:48:37 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*arrange_memory(t_block *block, size_t size)
{
	char		*new;
	enum e_type	type;

	if (size == block->size)
		return ((char *)block + B_SIZE);
	type = g_zone.type;
	new = (char *)malloc(size);
	ft_memmove(new, (char *)block + B_SIZE, block->size);
	g_zone.type = type;
	clear_memory(block);
	return (new);
}

void		*realloc(void *ptr, size_t size)
{
	size_t		new_size;
	t_block		*b;
	t_block		*r;

	if (!ptr)
		return (malloc(size));
	pthread_mutex_lock(&g_mutex);
	if (!(b = find_block(ptr)))
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	if (!size)
	{
		free(b);
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	new_size = ALIGN(size, 16);
	if (b->size > new_size)
	{
		split_block(b, new_size);
		r = b->next->next;
		if (r && r->free)
			merge_blocks(b->next, r);
		ptr = (char *)b + B_SIZE;
	}
	else
		ptr = arrange_memory(b, new_size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
