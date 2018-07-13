/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 13:47:55 by rsibiet           #+#    #+#             */
/*   Updated: 2017/04/18 13:47:59 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static size_t		pagesize(size_t size)
{
	if (size <= TINY)
		return (T_LEN);
	if (size <= SMALL)
		return (S_LEN);
	return (size + PAGE_SIZE);
}

static size_t		pagesize_2(char type, size_t size)
{
	if (type == 'T')
		return (T_LEN);
	if (type == 'S')
		return (S_LEN);
	return (size);
}

static t_page		*create_new_page(size_t size)
{
	t_page		*page;
	t_page		*last;
	size_t		page_size;

	page_size = pagesize(size);
	page = (t_page *)mmap(NULL, page_size,
				PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
	page->type = get_page_size(size);
	page->size = page_size - PAGE_SIZE;
	page->next = NULL;
	page->prev = NULL;
	page->first = NULL;
	if (page_0(NULL, 1) == NULL)
		page_0(page, 0);
	else
	{
		last = page_0(NULL, 1);
		while (last->next != NULL)
			last = last->next;
		last->next = page;
		page->prev = last;
	}
	return (page);
}

static void			first_split_block(t_block *b, size_t page_size)
{
	t_block		*new;

	if (page_size == b->size)
		return ;
	if (page_size < b->size + BLOCK_SIZE)
	{
		b->size = page_size;
		return ;
	}
	new = (t_block *)(BDATA(b) + b->size - 1);
	new->size = page_size - b->size - BLOCK_SIZE;
	new->next = b->next;
	new->prev = b;
	b->next = new;
	new->free = 1;
}

t_block				*create_new_block(size_t size)
{
	t_block		*block;
	t_page		*page;

	page = create_new_page(size);
	block = (t_block *)PDATA(page);
	block->size = size;
	block->next = NULL;
	block->prev = NULL;
	block->free = 0;
	if (page->type != 'L')
		first_split_block(block,
			pagesize_2(page->type, page->size) - 2 * BLOCK_SIZE);
	page->first = block;
	return (block);
}
