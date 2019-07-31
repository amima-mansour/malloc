/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:48:00 by amansour          #+#    #+#             */
/*   Updated: 2019/07/31 10:45:53 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	show_alloc_mem(void)
{
	size_t		total;

	//pthread_mutex_lock(&g_mutex);
	total = 0;
	ft_putstr("TINY : ");
	display_zone(g_zone.tiny, &total);
	ft_putstr("SMALL : ");
	display_zone(g_zone.small, &total);
	ft_putstr("LARGE : ");
	display_zone(g_zone.large, &total);
	ft_putstr("Total : ");
	ft_put_octet(total);
	ft_putendl(" octets");
	//pthread_mutex_unlock(&g_mutex);
}

void	show_alloc_mem_hex(void)
{
	//pthread_mutex_lock(&g_mutex);
	ft_putstr("---TINY-------------------------\n");
	display_zone_hex(g_zone.tiny);
	ft_putstr("---SMALL------------------------\n");
	display_zone_hex(g_zone.small);
	ft_putstr("---LARGE---------------------------\n");
	display_zone_hex(g_zone.large);
	//pthread_mutex_unlock(&g_mutex);
}
