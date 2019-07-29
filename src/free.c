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

	b1->size = b1->size + B_SIZE + b2->size;
	b2_next = b2->next;
	b1->next = b2_next;
	if (b2_next)
		b2_next->prev = b1;
	b2->next = NULL;
	b2->prev = NULL;
	b2->size = 0;
}

void	clear_memory(t_block *block)
{
	t_block	*l;
	t_block	*r;

	l = block->prev;
	r = block->next;
	block->free = 1;
    // ft_putstr("clear memory\n");
	if (g_zone.type == LARGE)
	{
		if (l)
			l->next = r;
		else
			g_zone.large = r;
		if (r)
			r->prev = l;
		munmap(block, block->size + B_SIZE);
	}
	else
	{
		if (r && r->free == 1)
			merge_blocks(block, r);
		if (l && l->free == 1)
			merge_blocks(l, block);
	}
    // ft_putstr("fn clear memory\n");

}

void	free(void *ptr)
{
	t_block		*b_exist;

    ft_putstr("free\n");
	if (ptr == NULL || !(b_exist = find_block(ptr)))
    {
        ft_putstr("fin free\n");
		return ;
    }
	clear_memory(b_exist);
    ft_putstr("fin free\n");
}
