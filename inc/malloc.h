/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:36:23 by amansour          #+#    #+#             */
/*   Updated: 2019/07/31 10:44:43 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <pthread.h>

# define BASE_16		"0123456789ABCDEF"
# define ALIGNEMENT		16
# define ALIGN(s, al)	((s + (al - 1))& ~(al - 1))
# define P_SIZE			getpagesize()
# define B_SIZE			ALIGN(sizeof(t_block), 16)
# define TINY_MAX			1024
# define SMALL_MAX		4096
# define MIN_ALLOC_NB	100

typedef enum			e_type
{
	TINY,
	SMALL,
	LARGE
}						t_type;

typedef struct			s_block
{
	size_t				size;
	char				free;
	struct s_block		*next;
	struct s_block		*prev;
}						t_block;

typedef struct			s_zone
{
	t_type				type;
	t_block				*tiny;
	t_block				*small;
	t_block				*large;
	t_block				**current;
}						t_zone;

t_zone					g_zone;

extern pthread_mutex_t	g_mutex;

/*
**	malloc.c
*/
void					*malloc(size_t size);

/*
**	free.c
*/
void					free(void *ptr);
void					clear_memory(t_block *block);
void					merge_blocks(t_block *b1, t_block *b2);

/*
** realloc.c
*/
void					*arrange_memory(t_block *block, size_t size);
void					*realloc(void *ptr, size_t size);

/*
**	calloc.c
*/
void					*calloc(size_t nmemb, size_t size);

/*
**	zones.c
*/
t_block					*find_addr_in_zone(t_block *blocks_zone, void *addr);
void					initialize_zone(size_t size);
void					display_zone(t_block *blocks, size_t *total);
void                    display_zone_hex(t_block *blocks);

/*
**	blocks.c
*/
t_block					*split_block(t_block *block, size_t size);
t_block					*last_block(t_block *b);
t_block					*create_space(size_t size, t_block *pre);
t_block					*free_place(t_block *block, size_t size);
t_block					*find_or_create_block(t_block **current, size_t size);
t_block					*find_block(void *ptr);
size_t					display_blocks(t_block *blocks);
void                    hexdump(void *addr, size_t size);

/*
**	tools.c
*/
void					ft_bzero(void *s, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);

/*
**	size.c
*/
size_t					get_right_mmmap_size(size_t size);

/*
** number.c
*/
void					ft_put_octet(size_t n);
void					ft_putnbr(int n);

/*
**	char.c
*/
void					ft_putchar(char c);

/*
**	string.c
*/
size_t					ft_strlen(const char *s);
void					ft_putstr(char const *s);
void					ft_putendl(char const *s);

/*
**	address.c
*/
void					ft_putaddr(unsigned long long int n);

/*
**	show_alloc_mem.c
*/
void					show_alloc_mem(void);

#endif
