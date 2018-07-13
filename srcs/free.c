/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:19:32 by rsibiet           #+#    #+#             */
/*   Updated: 2017/04/14 16:19:54 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern pthread_mutex_t		g_mutex;

static void		del_page(t_page *page)
{
	if (page->prev == NULL && page->next == NULL)
		page_0(NULL, 0);
	else if (page->prev != NULL)
		page->prev->next = page->next;
	else
		page_0(page->next, 0);
	if (page->next != NULL)
		page->next->prev = page->prev;
	munmap(page, page->size + PAGE_SIZE + 1);
}

static void		control_page(t_page *page, int not_free, int tiny, int small)
{
	t_block		*tmp;
	t_block		*memo;

	tmp = page->first;
	while (tmp != NULL)
	{
		if (tmp->free == 0)
			memo = tmp;
		else
			not_free++;
		tmp = tmp->next;
	}
	if (memo == NULL)
	{
		if (page->type == 'L' ||
			(not_free == 0 && page->type == 'T' && tiny > 1) ||
			(not_free == 0 && page->type == 'S' && small > 1))
			del_page(page);
	}
}

static void		resize_bk(t_block *b, t_page *page, int tiny, int small)
{
	t_block		*prev_bk;

	if (b == NULL)
		return ;
	prev_bk = b;
	if (b->next != NULL && b->next->free == 1)
		b = b->next;
	else if (prev_bk->prev != NULL && prev_bk->prev->free == 1)
		prev_bk = prev_bk->prev;
	prev_bk->free = 1;
	if (prev_bk == b)
		control_page(page, 0, tiny, small);
	else
	{
		prev_bk->size = b->size + prev_bk->size + BLOCK_SIZE;
		prev_bk->next = b->next;
		control_page(page, 0, tiny, small);
	}
}

static void		check_memory(void *ptr, t_page *page, int tiny, int small)
{
	t_block		*b;
	t_block		*b_memo;
	t_page		*p_memo;

	b_memo = NULL;
	p_memo = NULL;
	while (page != NULL)
	{
		b = page->first;
		if (page->type == 'T')
			tiny++;
		else if (page->type == 'S')
			small++;
		while (b != NULL)
		{
			if (ptr == BDATA(b))
			{
				b_memo = b;
				p_memo = page;
			}
			b = b->next;
		}
		page = page->next;
	}
	resize_bk(b_memo, p_memo, tiny, small);
}

void			free(void *ptr)
{
	t_page		*page;

	page = page_0(NULL, 1);
	if (ptr == NULL)
		return ;
	if (pthread_mutex_lock(&g_mutex) != 0)
	{
		ft_putstr("An error has occured with the mutex in free\n");
		return ;
	}
	check_memory(ptr, page, 0, 0);
	pthread_mutex_unlock(&g_mutex);
}
