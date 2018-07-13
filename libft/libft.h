/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:00:19 by rsibiet           #+#    #+#             */
/*   Updated: 2017/02/13 18:58:44 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>

void				ft_putchar(char c);
int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *scr, size_t n);
void				ft_putnbr(int n);
void				ft_putstr(char const *s);
size_t				ft_strlen(const char *s);
void				ft_put_addr(void *addr);

#endif
