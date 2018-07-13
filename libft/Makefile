# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/25 10:49:22 by rsibiet           #+#    #+#              #
#    Updated: 2017/04/14 15:04:01 by rsibiet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FTC = ft_bzero.c \
	  ft_memcpy.c \
	  ft_atoi.c \
	  ft_putchar.c \
	  ft_putstr.c \
	  ft_putnbr.c \
	  ft_strlen.c \
	  ft_itoa_hex.c

FTO = $(subst .c,.o,$(FTC))

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(FTO)
	@ar rc $(NAME) $(FTO)
	@ranlib $(NAME)
	@echo ""
	@echo ""
	@echo "\033[32m• $(NAME) created!\033[0m"
	@echo ""
	@echo ""
	@echo "\033[0m--------------------------------------------------------------"

%.o: %.c
	@gcc -Wall -Wextra -Werror -c $<
	@echo "\033[42m   \033[0m\c"

clean:
	@rm -rf $(FTO)

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[31;1m• \033[31mLibft deleted!\033[0m"

fcleana:
	@rm -rf $(FTO)
	@rm -rf $(NAME)
	@echo "\033[31;1m• \033[31mLibft deleted!\033[0m"

re: fclean all
