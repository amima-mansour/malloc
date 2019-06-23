#include "../inc/malloc.h"

void *calloc (size_t nmemb, size_t size)
{
	void	*block;

	if ((int)nmemb < 0 || (int)size < 0)
		return (NULL);
	if ((block = malloc(nmemb * size)))
		ft_bzero(block, nmemb * size);
	return (block);
}
