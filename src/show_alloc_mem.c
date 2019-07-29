/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:48:00 by amansour          #+#    #+#             */
/*   Updated: 2019/07/29 09:10:33 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	show_alloc_mem(void)
{
	size_t		total;

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
}
