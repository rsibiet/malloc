/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 14:13:47 by rsibiet           #+#    #+#             */
/*   Updated: 2017/04/14 16:18:13 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <stdio.h>

pthread_mutex_t		g_mutex = PTHREAD_MUTEX_INITIALIZER;

char				get_page_size(size_t size)
{
	if (size <= TINY)
		return ('T');
	if (size <= SMALL)
		return ('S');
	return ('L');
}

static t_block		*free_bk_in_page(t_page *page, size_t size)
{
	t_block				*b;

	b = page->first;
	while (b != NULL && (b->free == 0 || b->size <= (size + BLOCK_SIZE)))
		b = b->next;
	return (b);
}

void				split_block(t_block *b, size_t size)
{
	t_block				*new;

	if (size == b->size)
		return ;
	new = (t_block *)(BDATA(b) + size);
	new->size = b->size - size - BLOCK_SIZE;
	new->next = b->next;
	new->prev = b;
	b->size = size;
	b->next = new;
	new->free = 1;
}

static t_block		*get_free_block(size_t size)
{
	t_page				*page;
	t_block				*b;

	page = page_0(NULL, 1);
	b = NULL;
	while (page != NULL)
	{
		if (page->type == get_page_size(size) &&
			(b = free_bk_in_page(page, size)) != NULL)
		{
			split_block(b, size);
			b->free = 0;
			return (b);
		}
		page = page->next;
	}
	return (NULL);
}

void				*malloc(size_t size)
{
	t_block				*b;

	if (pthread_mutex_lock(&g_mutex) != 0)
	{
		ft_putstr("An error has occured with the mutex in malloc\n");
		return (NULL);
	}
	if ((b = get_free_block(size)) == NULL)
		b = create_new_block(size);
	pthread_mutex_unlock(&g_mutex);
	return (BDATA(b));
}
