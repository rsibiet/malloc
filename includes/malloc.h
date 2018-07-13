/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 10:49:07 by rsibiet           #+#    #+#             */
/*   Updated: 2017/04/14 15:56:16 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define BLOCK_SIZE	(sizeof(t_block))
# define BDATA(b)	((void*)((char*)b + sizeof(t_block) + 1))

# define PAGE_SIZE	(sizeof(t_page))
# define PDATA(p)	((void*)((char*)p + sizeof(t_page) + 1))

# define TINY 	(size_t)(getpagesize() / 32)
# define T_LEN	getpagesize()

# define SMALL	(size_t)(getpagesize() / 4)
# define S_LEN	(8 * getpagesize())

# include "../libft/libft.h"
# include <unistd.h>
# include <sys/mman.h>
# include <stdlib.h>
# include <pthread.h>

struct s_block;

/*
** Pages contains blocks
** type: T = TINY
**		 S = SMALL
**		 L = LARGE
*/

typedef struct			s_page
{
	char				type;
	size_t				size;
	struct s_page		*next;
	struct s_page		*prev;
	struct s_block		*first;
}						t_page;

/*
** 1 block = 1 malloc
** chunk used: free = 0;
** chunk not used: free = 1;
*/

typedef struct			s_block
{
	size_t				size;
	struct s_block		*next;
	struct s_block		*prev;
	int					free;
}						t_block;

void					*malloc(size_t size);
char					get_page_size(size_t size);
t_block					*create_new_block(size_t size);
t_page					*page_0(t_page *page, int i);
void					free(void *ptr);
void					split_block(t_block *b, size_t size);
void					*realloc(void *ptr, size_t size);
void					show_alloc_mem(void);

#endif
