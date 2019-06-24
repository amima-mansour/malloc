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
	if (g_zone.type == TINY)
		return (ALIGN((TINY_MAX + B_SIZE * MIN_ALLOC_NB), P_SIZE));
	if (g_zone.type == SMALL)
		return (ALIGN((SMALL_MAX + B_SIZE * MIN_ALLOC_NB), P_SIZE));
	return (ALIGN(size + B_SIZE, P_SIZE));
}
