/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:36:52 by amansour          #+#    #+#             */
/*   Updated: 2019/06/27 17:24:11 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_block		*split_block(t_block *block, size_t size)
{
	t_block		*new_block;
	t_block		*right;
	size_t		total_size;

	right = block->next;
	total_size = block->size + B_SIZE;
	new_block = (t_block *)((char *)block + B_SIZE + size);
	new_block->size = total_size - size - 2 * B_SIZE;
	new_block->free = 1;
	new_block->prev = block;
	new_block->next = right;
	block->size = size;
	block->next = new_block;
	if (right)
		right->prev = new_block;
	return (block);
}

t_block		*create_space(size_t size, t_block *previous)
{
	t_block		*block;
	size_t		new_size;

	new_size = get_right_mmmap_size(size);
	block = mmap(0, new_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE,
				-1, 0);
	if (block == MAP_FAILED)
		return (NULL);
	block->free = 0;
	block->size = new_size;
	block->next = NULL;
    block->prev = previous;
	if (previous)
		previous->next = block;
	return (block);
}

void		*free_place(size_t size, t_block *block)
{
	while (block)
	{
		if (block->size >= size && block->free)
			return (block);
		if(!block->next)
            break ;
        block = block->next;
	}
	return (block);
}

t_block		*find_or_create_block(size_t size, t_block **current)
{
	t_block *block;

	if (!*current)
    {
        *current = create_space(size, *current);
        return (*current);
    }
    block = free_place(size, *current);
	if (block->size >= size && block->free)
        return (split_block(block, size));
	return (create_space(size, block));
}

t_block		*find_block(void *ptr)
{
	t_block		*block;

	pthread_mutex_lock(&g_mutex);
	block = find_addr_in_zone(g_zone.large, ptr);
	if (block == NULL)
	{
		block = find_addr_in_zone(g_zone.small, ptr);
		if (block == NULL)
		{
			block = find_addr_in_zone(g_zone.tiny, ptr);
			g_zone.type = TINY;
		}
		else
			g_zone.type = SMALL;
	}
	else
		g_zone.type = LARGE;
	pthread_mutex_unlock(&g_mutex);
	return (block);
}
