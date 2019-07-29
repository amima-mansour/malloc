/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:37:48 by amansour          #+#    #+#             */
/*   Updated: 2019/07/29 09:14:04 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	*calloc(size_t nmemb, size_t size)
{
	void	*block;

    ft_putstr("calloc\n");
	if ((block = malloc(nmemb * size)))
		ft_bzero(block, nmemb * size);
    ft_putstr("fin callloc\n");
	return (block);
}
