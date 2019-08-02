/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:37:48 by amansour          #+#    #+#             */
/*   Updated: 2019/08/02 12:37:04 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t nmemb, size_t size)
{
	void	*block;

	if ((int)size < 0 || (int)nmemb < 0)
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	if ((block = malloc(nmemb * size)))
		ft_bzero(block, nmemb * size);
	pthread_mutex_unlock(&g_mutex);
	return (block);
}
