/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:39:51 by amansour          #+#    #+#             */
/*   Updated: 2019/06/24 14:40:43 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void		ft_putnbr(int n)
{
	if (n / 10 == 0 && n % 10 < 0)
	{
		ft_putchar('-');
		ft_putchar(-1 * (n % 10) + '0');
	}
	else if (n / 10 == 0)
		ft_putchar(n % 10 + '0');
	else
	{
		ft_putnbr(n / 10);
		if (n < 0)
			ft_putchar(-1 * (n % 10) + '0');
		else
			ft_putchar(n % 10 + '0');
	}
}

void		ft_put_octet(size_t n)
{
	if (n / 10 == 0)
		ft_putchar(n % 10 + '0');
	else
	{
		ft_put_octet(n / 10);
		ft_putchar(n % 10 + '0');
	}
}
