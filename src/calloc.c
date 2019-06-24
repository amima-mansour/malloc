/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:37:48 by amansour          #+#    #+#             */
/*   Updated: 2019/06/24 14:37:58 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void *calloc (size_t nmemb, size_t size)
{
	void	*block;

	if ((int)nmemb < 0 || (int)size < 0)
		return (NULL);
	if ((block = malloc(nmemb * size)))
		ft_bzero(block, nmemb * size);
	return (block);
}
