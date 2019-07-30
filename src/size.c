/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:41:29 by amansour          #+#    #+#             */
/*   Updated: 2019/06/24 14:41:41 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

size_t	get_right_mmmap_size(size_t size)
{
	size_t	s;

	if (g_zone.type == TINY)
		s = (TINY_MAX + B_SIZE) * MIN_ALLOC_NB;
	else if (g_zone.type == SMALL)
		s = (SMALL_MAX + B_SIZE) * MIN_ALLOC_NB;
	else
		s = size + B_SIZE;
	return (ALIGN(s, P_SIZE));
}