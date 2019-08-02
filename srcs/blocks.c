/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:36:52 by amansour          #+#    #+#             */
/*   Updated: 2019/08/02 09:38:44 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block			*split_block(t_block *block, size_t size)
{
	t_block		*new_block;
	t_block		*right;
	size_t		total_size;

	right = block->next;
	total_size = block->size + B_SIZE;
	new_block = (t_block *)((char *)block + B_SIZE + size);
	new_block->size = total_size - size - B_SIZE * 2;
	new_block->free = 1;
	new_block->prev = block;
	new_block->next = block->next;
	block->size = size;
	block->next = new_block;
	if (right)
		right->prev = new_block;
	return (block);
}

static t_block	*create_space(size_t size, t_block *prev)
{
	t_block	*b;
	size_t	mmap_size;

	mmap_size = get_right_mmmap_size(size);
	b = mmap(0, mmap_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE,
				-1, 0);
	if (b == MAP_FAILED)
		return (NULL);
	b->free = 1;
	b->size = mmap_size - B_SIZE;
	b->next = NULL;
	b->prev = prev;
	if (prev)
		prev->next = b;
	return (b);
}

static t_block	*free_place(t_block *blocks, size_t size)
{
	while (blocks)
	{
		if (blocks->size >= size && blocks->free)
			return (blocks);
		if (!blocks->next)
			break ;
		blocks = blocks->next;
	}
	return (blocks);
}

t_block			*find_or_create_block(t_block **blocks, size_t size)
{
	t_block		*ptr;

	if (!*blocks)
	{
		*blocks = create_space(size, *blocks);
		return (*blocks);
	}
	ptr = free_place(*blocks, size);
	if (ptr->size >= size && ptr->free == 1)
		return (ptr);
	else
		return (create_space(size, ptr));
}

t_block			*find_block(void *ptr)
{
	t_block		*block;

	block = find_addr_in_zone(g_zone.large, ptr);
	if (block == NULL)
	{
		block = find_addr_in_zone(g_zone.small, ptr);
		if (block == NULL)
		{
			block = find_addr_in_zone(g_zone.tiny, ptr);
			if (block == NULL)
				return (NULL);
			g_zone.type = TINY;
		}
		else
			g_zone.type = SMALL;
	}
	else
		g_zone.type = LARGE;
	return (block);
}
