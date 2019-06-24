/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:47:37 by amansour          #+#    #+#             */
/*   Updated: 2019/06/24 14:40:56 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	*arrange_memory(t_block *block, size_t size)
{
	char		*new;
	enum e_type	type;

	pthread_mutex_lock(&g_mutex);
	type = g_zone.type;
	new = (char *)malloc(size);
	ft_memmove(new, (char *)block + B_SIZE, block->size);
	g_zone.type = type;
	clear_memory(block);
	pthread_mutex_unlock(&g_mutex);
	return (new);
}

void		*realloc(void *ptr, size_t size)
{
	size_t		new_size;
	t_block		*b;

	if ((int)size < 0)
		return (NULL);
	if (!ptr)
		return (malloc(size));
	if (!(b = find_block(ptr)))
		return (NULL);
	new_size = ALIGN(size, ALIGNEMENT);
	if (b->size >= new_size)
		return (ptr);
	return (arrange_memory(b, new_size));
}
