/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:47:37 by amansour          #+#    #+#             */
/*   Updated: 2019/07/29 09:14:55 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	*arrange_memory(t_block *block, size_t size)
{
	char		*new;
	enum e_type	old_type;

	old_type = g_zone.type;
	new = (char *)malloc(size);
	ft_memmove(new, (char *)block + B_SIZE, block->size);
	g_zone.type = old_type;
	clear_memory(block);
	return (new);
}

void		*realloc(void *ptr, size_t size)
{
	size_t		new_size;
	t_block		*b;

	if (!ptr)
		return (malloc(size));
	b = find_block(ptr);
	if (!b)
		return (NULL);
	new_size = ALIGN(size, 16);
	if (b->size >= new_size)
		return (ptr);
	return (arrange_memory(b, new_size));
}
