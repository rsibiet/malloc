# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/25 10:49:22 by rsibiet           #+#    #+#              #
#    Updated: 2017/04/18 13:55:12 by rsibiet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_LIB = libft_malloc_$(HOSTTYPE).so

FTC = srcs/malloc.c \
	  srcs/new_block.c \
	  srcs/free.c \
	  srcs/realloc.c \
	  srcs/show_alloc_mem.c

FTO = $(subst .c,.o,$(FTC))

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

all: $(NAME_LIB)

$(NAME_LIB): $(FTO)
	@make -C ./libft/
	gcc -Wall -Wextra -Werror -shared -o $(NAME_LIB) $(FTO) -I ./includes/ -Llibft -lft
	ln -F -s libft_malloc_$(HOSTTYPE).so libft_malloc.so
	@echo "\033[32m• $(NAME_LIB) created!\033[0m"
	@echo ""
	@echo "\033[0m--------------------------------------------------------------"
	@echo ""

clean:
	@make -C ./libft/ clean
	rm -rf $(FTO)
	rm -rf libft_malloc.so
	rm -rf libft_malloc_$(HOSTTYPE).so
	@echo "\033[33m• Libft_malloc object deleted!\033[0m"

fclean: clean
	make -C ./libft/ fclean
	@rm -rf $(NAME)
	@echo "\033[31;1m• \033[31mLibft_malloc deleted!\033[0m"

re: fclean all
