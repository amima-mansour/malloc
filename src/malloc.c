/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:47:23 by amansour          #+#    #+#             */
/*   Updated: 2019/07/31 10:48:15 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*malloc(size_t size)
{
	t_block		*ptr;
	size_t		new_size;

	new_size = ALIGN(size, 16);
	initialize_zone(new_size);
	ptr = find_or_create_block(g_zone.current, new_size);
	if (!ptr)
		return (NULL);
	if (g_zone.type != LARGE && ptr->size > new_size + B_SIZE)
		split_block(ptr, new_size);
	ptr->free = 0;
	return ((char *)ptr + B_SIZE);
}
