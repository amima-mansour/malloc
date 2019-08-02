/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:48:37 by amansour          #+#    #+#             */
/*   Updated: 2019/08/02 09:40:27 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	merge_blocks(t_block *b1, t_block *b2)
{
	t_block		*b2_next;

	if ((char *)b1 + B_SIZE + b1->size == (char *)b2)
	{
		b1->size = b1->size + B_SIZE + b2->size;
		b2_next = b2->next;
		b1->next = b2_next;
		if (b2_next)
			b2_next->prev = b1;
		b2->next = NULL;
		b2->prev = NULL;
		b2->size = 0;
	}
}

void	clear_memory(t_block *block)
{
	t_block	*l;
	t_block	*r;

	block->free = 1;
	l = block->prev;
	r = block->next;
	if (g_zone.type == LARGE)
	{
		if (l)
			l->next = block->next;
		else
			g_zone.large = r;
		if (r)
			r->prev = block->prev;
		munmap(block, block->size + B_SIZE);
	}
	else
	{
		if (r && r->free == 1)
			merge_blocks(block, r);
		if (l && l->free == 1)
			merge_blocks(l, block);
	}
}

void	free(void *ptr)
{
	t_block		*b;

	if (ptr == NULL)
		return ;
	pthread_mutex_lock(&g_mutex);
	if (!(b = find_block(ptr)))
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	clear_memory(b);
	pthread_mutex_unlock(&g_mutex);
}
