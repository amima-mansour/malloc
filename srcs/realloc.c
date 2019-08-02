/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:47:37 by amansour          #+#    #+#             */
/*   Updated: 2019/08/02 12:41:32 by amansour         ###   ########.fr       */
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
	t_block		*b;

	if ((int)size < 0)
		return (NULL);
	if (!ptr)
		return (malloc(size));
	pthread_mutex_lock(&g_mutex);
	if (!(b = find_block(ptr)) || (b && !size))
	{
		if (b)
			free(b);
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	if (b->size > ALIGN(size, ALIGNEMENT))
	{
		split_block(b, ALIGN(size, ALIGNEMENT));
		if (b->next->next && b->next->next->free)
			merge_blocks(b->next, b->next->next);
		ptr = (char *)b + B_SIZE;
	}
	else
		ptr = arrange_memory(b, ALIGN(size, ALIGNEMENT));
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
