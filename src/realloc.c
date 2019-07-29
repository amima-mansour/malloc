/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:47:37 by amansour          #+#    #+#             */
/*   Updated: 2019/07/29 09:14:55 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	*arrange_memory(t_block *block, size_t size)
{
	char		*new;
	enum e_type	type;
	size_t		min;

	type = g_zone.type;
	new = (char *)malloc(size);
	ft_putstr("SIZE = ");
	ft_putnbr(size);
	ft_putstr("\n");
	min = size < block->size ? size: block->size;
	ft_putstr("MIN = ");
	ft_putnbr(min);
	ft_putstr("\n");
	ft_memmove(new, (char *)block + B_SIZE, min);
	g_zone.type = type;
	if (g_zone.type == SMALL)
		ft_putstr("SMALL\n");
	else if (g_zone.type == LARGE)
		ft_putstr("LARGE\n");
	else
		ft_putstr("TINY\n");
	free(block);
    ft_putstr("fin realloc\n");
	return (new);
}

void	*realloc(void *ptr, size_t size)
{
	size_t		new_size;
	t_block		*b;
	//t_block		*p;

    ft_putstr("realloc\n");
	if (!(ptr))
        return (malloc(size));
	if (size == 0)
	{
		ft_putstr("size null \n");
		free(ptr);
		return (NULL);
	}
	if (!(b = find_block(ptr)))
	{
		ft_putstr("not exists\n");
		return (NULL);
	}
	
	new_size = ALIGN(size, ALIGNEMENT);
	ft_putnbr(new_size);
	ft_putstr("\n");
	ft_putnbr(b->size);
	ft_putstr("\n");
	return (arrange_memory(b, new_size));
}
