/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:47:23 by amansour          #+#    #+#             */
/*   Updated: 2019/07/29 09:13:17 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

pthread_mutex_t		g_mutex = PTHREAD_MUTEX_INITIALIZER;

void				*malloc(size_t size)
{
	t_block		*bp;
	size_t		new_size;
    
    //ft_putstr("malloc\n");
	new_size = ALIGN(size, ALIGNEMENT);
	initialize_zone(new_size);
	bp = find_or_create_block(new_size, g_zone.current);
	//ft_putstr("fin malloc\n");
    return ((char*)bp + B_SIZE);
}
