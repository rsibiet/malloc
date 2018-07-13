/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 16:18:42 by rsibiet           #+#    #+#             */
/*   Updated: 2017/04/14 16:19:11 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern pthread_mutex_t		g_mutex;

/*
** realloc(array, 0) est pas équivalent à free(array)
** realloc(NULL, size) est equivalent à malloc(size)
*/

static void		*try_to_resize(char page_type, t_block *b,
								size_t size, void *ptr)
{
	void	*ptr2;

	ptr2 = ptr;
	if (page_type == 'L' || b->next == NULL || b->next->free == 0 ||
		(b->size + b->next->size) < (size + BLOCK_SIZE + 1))
	{
		pthread_mutex_unlock(&g_mutex);
		ptr = malloc(size);
		pthread_mutex_lock(&g_mutex);
		if (size > b->size)
			size = b->size;
		ft_memcpy(ptr, ptr2, size);
		pthread_mutex_unlock(&g_mutex);
		free(ptr2);
		pthread_mutex_lock(&g_mutex);
	}
	else if (size < b->size)
		split_block(b, size);
	else
	{
		b->next->size += b->size - size;
		b->size = size;
	}
	return (ptr);
}

static void		*find_block(void *ptr, size_t size, t_page *page, t_block *b)
{
	while (page != NULL)
	{
		b = page->first;
		while (b != NULL)
		{
			if (ptr == BDATA(b))
				break ;
			b = b->next;
		}
		if (b != NULL)
			break ;
		page = page->next;
	}
	if ((size == 0 && b != NULL) || (b != NULL && size == b->size))
		return (ptr);
	else if (size == 0 || b == NULL)
		return (NULL);
	ptr = try_to_resize(page->type, b, size, ptr);
	return (ptr);
}

void			*realloc(void *ptr, size_t size)
{
	t_page		*page;

	page = page_0(NULL, 1);
	if (pthread_mutex_lock(&g_mutex) != 0)
	{
		ft_putstr("An error has occured with the mutex in realloc\n");
		return (NULL);
	}
	if (ptr == NULL)
	{
		pthread_mutex_unlock(&g_mutex);
		return (malloc(size));
		pthread_mutex_lock(&g_mutex);
	}
	ptr = find_block(ptr, size, page, NULL);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
