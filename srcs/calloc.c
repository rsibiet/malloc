/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 17:20:26 by rsibiet           #+#    #+#             */
/*   Updated: 2017/04/20 17:20:28 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern pthread_mutex_t		g_mutex;

void		*calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (pthread_mutex_lock(&g_mutex) != 0)
	{
		ft_putstr("An error has occured with the mutex in calloc\n");
		return (NULL);
	}
	pthread_mutex_unlock(&g_mutex);
	ptr = malloc(nmemb * size);
	pthread_mutex_lock(&g_mutex);
	ft_bzero(ptr, nmemb * size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
