/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:38:32 by amansour          #+#    #+#             */
/*   Updated: 2019/06/27 17:25:48 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	ft_puthex(unsigned char c)
{
	ft_putchar(BASE_16[c / 16]);
	ft_putchar(BASE_16[c % 16]);
}

void	write_hexa_characters(void *addr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < 16 && i < size)
	{
		ft_puthex(*((unsigned char *)addr + i));
		ft_putchar(' ');
		if (i / 16 == 2)
			ft_putchar(' ');
		i++;
	}
	if (i < 8)
		ft_putchar(' ');
	while (i++ < 16)
		ft_putstr("  ");
}

void	write_characters(void *addr, size_t size)
{
	size_t			i;
	unsigned char	c;

	i = 0;
	ft_putchar('|');
	while (i < 16 && i < size)
	{
		c = *((unsigned char *)addr + i);
		if (c >= 32 && c <= 126)
			ft_putchar(c);
		else
			ft_putchar('.');
		i++;
	}
	ft_putchar('|');
}

void	hexdump_line(void *addr, size_t size)
{
	ft_putaddr((unsigned long long)addr);
	ft_putstr("  ");
	write_hexa_characters(addr, size);
	write_characters(addr, size);
	ft_putchar('\n');
}

void	hexdump(void *addr, size_t size)
{
	hexdump_line(addr, size);
	size -= 16;
	if (size > 0)
	{
		addr += 16;
		hexdump(addr, size);
	}
}
