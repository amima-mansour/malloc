

#include "malloc.h"

size_t		display_blocks(t_block *blocks)
{
	char	*start;
	char	*end;
	size_t	total;

	total = 0;
	while (blocks)
	{
		if (blocks->free == 0)
		{
			start = (char *)blocks + B_SIZE;
			end = (char *)blocks + B_SIZE + blocks->size;
			ft_putaddr((unsigned long long)start);
			ft_putstr(" - ");
			ft_putaddr((unsigned long long)end);
			ft_putstr(" : ");
			ft_put_octet((size_t)(end - start));
			ft_putendl(" octets");
			total += (size_t)(end - start);
		}
		blocks = blocks->next;
	}
	return (total);
}
