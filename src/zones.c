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

t_block		*find_addr_in_zone(t_block *blocks_zone, void *addr)
{
    ft_putstr("find address\n");
	while (blocks_zone)
	{
		// ft_putnbr(blocks_zone->free);
		// ft_putstr("\n");
		// if (g_zone.type == SMALL)
		// 	ft_putstr("SMALL\n");
		// else if (g_zone.type == LARGE)
		// 	ft_putstr("LARGE\n");
		// else
		// 	ft_putstr("TINY\n");	
		// ft_putstr("\n");
		if ((unsigned char *)blocks_zone + B_SIZE == (unsigned char *)addr)
			return (blocks_zone);
		//sleep(0.5);
		blocks_zone = blocks_zone->next;

	}
    ft_putstr("fin find address\n");
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
