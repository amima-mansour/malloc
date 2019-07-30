/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:47:23 by amansour          #+#    #+#             */
/*   Updated: 2019/07/29 09:13:17 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

static void		allocate_block(t_block *block, size_t size)
{
	if (g_zone.type != LARGE && block->size > size + B_SIZE)
		split_block(block, size);
	block->free = 0;
}

void			*malloc(size_t size)
{
	t_block		*alloc_b;
	size_t		new_size;

	new_size = ALIGN(size, 16);
	initialize_zone(new_size);
	alloc_b = find_or_create_block(g_zone.current, new_size);
	if (!alloc_b)
		return (NULL);
	allocate_block(alloc_b, new_size);
	return ((char *)alloc_b + B_SIZE);
}
