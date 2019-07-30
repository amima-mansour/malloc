/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:28:55 by amansour          #+#    #+#             */
/*   Updated: 2019/07/29 09:32:01 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void		initialize_zone(size_t size)
{
	if (size <= TINY_MAX)
	{
		g_zone.type = TINY;
		g_zone.current = &g_zone.tiny;
	}
	else if (size <= SMALL_MAX)
	{
		g_zone.type = SMALL;
		g_zone.current = &g_zone.small;
	}
	else
	{
		g_zone.type = LARGE;
		g_zone.current = &g_zone.large;
	}
}

t_block	*find_addr_in_zone(t_block *blocks, void *ptr)
{
	while (blocks)
	{
		if ((unsigned char *)blocks + B_SIZE == (unsigned char *)ptr)
			return (blocks);
		blocks = blocks->next;
	}
	return (NULL);
}

void		display_zone(t_block *block, size_t *total)
{
	if (block == NULL)
		ft_putendl("NOTHING");
	else
	{
		ft_putaddr((unsigned long long)block);
		ft_putstr("\n");
		*total += display_blocks(block);
	}
}
