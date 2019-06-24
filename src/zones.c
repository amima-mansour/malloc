#include "../inc/malloc.h"

void    initialize_zone(size_t size)
{
    if (size <= TINY_MAX)
	{
		g_zone.type = TINY;
		g_zone.current = g_zone.tiny;
	}
	else if (size <= SMALL_MAX)
	{
		g_zone.type = SMALL;
		g_zone.current = g_zone.small;
	}
	else
	{
		g_zone.type = LARGE;
		g_zone.current = g_zone.large;
	}
}

t_block   *find_addr_in_zone(t_block *blocks_zone, void *addr)
{
    while (blocks_zone)
	{
		if ((unsigned char *)blocks_zone + B_SIZE == (unsigned char *)addr)
			return (blocks_zone);
		blocks_zone = blocks_zone->next;
	}
	return (blocks_zone);
}

void	display_zone(t_block *block, size_t *total)
{
	if (block == NULL)
		ft_putendl("NOTHING");
	else
	{
		ft_putaddr((unsigned long long)block);
		ft_putstr("\n");
		*total += display_blocks(block);
	}
}

void	display_zone_hex(t_block *block)
{
	int		total;

	total = 0;
	while (block)
	{
		if (block->free == 0)
		{
			hexdump((char *)block + B_SIZE, block->size);
			total++;
		}
		block = block->next;
	}
	if (total == 0)
		ft_putstr("No allocation in this type of zone\n");
}