#include "../inc/malloc.h"

void	show_alloc_mem_ex(void)
{
	pthread_mutex_lock(&g_mutex);
	ft_putstr("TINY : ");
	display_zone_ex(g_zone.tiny);
	ft_putstr("SMALL : ");
	display_zone_ex(g_zone.small);
	ft_putstr("LARGE : ");
	display_zone_ex(g_zone.large);
	pthread_mutex_unlock(&g_mutex);

}