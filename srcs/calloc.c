/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:37:48 by amansour          #+#    #+#             */
/*   Updated: 2019/08/02 09:38:58 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t nmemb, size_t size)
{
	void	*block;

	pthread_mutex_lock(&g_mutex);
	if ((block = malloc(nmemb * size)))
		ft_bzero(block, nmemb * size);
	pthread_mutex_unlock(&g_mutex);
	return (block);
}
