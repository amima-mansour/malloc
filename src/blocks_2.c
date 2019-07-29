/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:14:52 by amansour          #+#    #+#             */
/*   Updated: 2019/06/27 17:20:55 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_block		*last_block(t_block *block)
{

	while (block && block->next)
	{
		block = block->next;
	}
	return (block);
}

size_t		display_blocks(t_block *blocks)
{
	char	*start;
	char	*end;
	size_t	total;

	total = 0;
	while (blocks)
	{
		if (blocks->free == 0)
		{
			start = (char *)blocks + B_SIZE;
			end = (char *)blocks + B_SIZE + blocks->size;
			ft_putaddr((unsigned long long)start);
			ft_putstr(" - ");
			ft_putaddr((unsigned long long)end);
			ft_putstr(" : ");
			ft_put_octet((size_t)(end - start));
			ft_putendl(" octets");
			total += (size_t)(end - start);
		}
		blocks = blocks->next;
	}
	return (total);
}
