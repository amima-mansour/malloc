/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:36:32 by amansour          #+#    #+#             */
/*   Updated: 2019/06/24 14:36:44 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	ft_putaddr(unsigned long long int n)
{
	if (n / 16 == 0)
	{
		ft_putstr("0x");
		ft_putchar(BASE_16[n % 16]);
	}
	else
	{
		ft_putaddr(n / 16);
		ft_putchar(BASE_16[n % 16]);
	}
}
