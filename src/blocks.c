/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:36:52 by amansour          #+#    #+#             */
/*   Updated: 2019/07/29 09:36:59 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"
#include <stdio.h>

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
	block->free = 1;
	block->size = new_size - B_SIZE;
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
		{
			ft_putstr("free block ->size = ");
			ft_putnbr(block->size);
			ft_putstr("\nThere is a free block\n");
			return (block);
		}
		if(!block->next)
            break ;
        block = block->next;
	}
	ft_putstr("no free block\n");
	return (block);
}

t_block		*find_or_create_block(size_t size, t_block **current)
{
	t_block *block;

	if (current == &g_zone.large)
		ft_putstr("LARGE\n");
	else if (current == &g_zone.small)
		ft_putstr("SMALL\n");
	else
		ft_putstr("TINY\n");
	if (!*current)
    {
		ft_putstr("Initialize zone\n");
		ft_putnbr(size);
		ft_putstr("\n");
        *current = create_space(size, *current);
        return (*current);
    }
	ft_putstr("zone exists\n");
	ft_putnbr(size);
	ft_putstr("\n");
    block = free_place(size, *current);
	if (block->size >= size && block->free)
        return (split_block(block, size));
	return (create_space(size, block));
}

t_block		*find_block(void *ptr)
{
	t_block		*block;

    ft_putstr("find block\n");
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
	ft_putstr("fin find block\n");
    return (block);
}
