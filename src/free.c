/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:48:37 by amansour          #+#    #+#             */
/*   Updated: 2019/07/29 09:41:17 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

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
	t_block	*left;
	t_block	*right;

	block->free = 1;
	left = block->prev;
	right = block->next;
	if (g_zone.type == LARGE)
	{
		if (left)
			left->next = block->next;
		else
			g_zone.large = NULL;
		if (right)
			right->prev = block->prev;
		munmap(block, block->size + B_SIZE);
	}
	else
	{
		if (right && right->free == 1)
			merge_blocks(block, right);
		if (left && left->free == 1)
			merge_blocks(left, block);
	}

}

void	free(void *ptr)
{
	t_block		*b_exist;

	if (ptr == NULL)
		return ;
	b_exist = find_block(ptr);
	if (!b_exist)
		return ;
	clear_memory(b_exist);
}