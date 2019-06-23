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

void		ft_putnbr_fd(int n, int fd)
{
	if (n / 10 == 0 && n % 10 < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd(-1 * (n % 10) + '0', fd);
	}
	else if (n / 10 == 0)
		ft_putchar_fd(n % 10 + '0', fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		if (n < 0)
			ft_putchar_fd(-1 * (n % 10) + '0', fd);
		else
			ft_putchar_fd(n % 10 + '0', fd);
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