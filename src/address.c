#include "../inc/malloc.h"

void	ft_putaddr(unsigned long long int n)
{
	if (n / 16 == 0)
	{
		ft_putstr("0x");
		ft_putchar(BASE[n % 16]);
	}
	else
	{
		ft_putaddr(n / 16);
		ft_putchar(BASE[n % 16]);
	}
}

void	ft_putaddr_fd(unsigned long long int n, int fd)
{

	if (n / 16 == 0)
	{
		ft_putstr_fd("0x", fd);
		ft_putchar_fd(BASE[n % 16], fd);
	}
	else
	{
		ft_putaddr_fd(n / 16, fd);
		ft_putchar_fd(BASE[n % 16], fd);
	}
}