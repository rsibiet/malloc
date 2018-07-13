/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 13:52:31 by rsibiet           #+#    #+#             */
/*   Updated: 2017/04/16 13:53:35 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern pthread_mutex_t		g_mutex;

t_page				*page_0(t_page *page, int i)
{
	static t_page				*tp = NULL;

	if (i == 0)
		tp = page;
	return (tp);
}

static void			show_blocks(t_block *b)
{
	while (b != NULL)
	{
		if (b->free == 1)
			return ;
		ft_put_addr(BDATA(b));
		ft_putstr(" - ");
		ft_put_addr(BDATA(b) + b->size);
		ft_putstr(" : ");
		ft_putnbr((int)b->size);
		ft_putstr(" octets\n");
		b = b->next;
	}
}

void				show_alloc_mem(void)
{
	t_page						*page;
	t_block						*b;

	if (pthread_mutex_lock(&g_mutex) != 0)
	{
		ft_putstr("An error has occured with the mutex in show_alloc_mem\n");
		return ;
	}
	if ((page = page_0(NULL, 1)) == NULL)
		ft_putstr("No memory allocated\n");
	while (page != NULL)
	{
		b = page->first;
		if (page->type == 'T')
			ft_putstr("TINY : ");
		else if (page->type == 'S')
			ft_putstr("SMALL : ");
		else
			ft_putstr("LARGE : ");
		ft_put_addr(page);
		ft_putchar('\n');
		show_blocks(b);
		page = page->next;
	}
	pthread_mutex_unlock(&g_mutex);
}
