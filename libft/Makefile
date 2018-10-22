# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srheede <srheede@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/26 15:30:46 by srheede           #+#    #+#              #
#    Updated: 2018/10/22 14:00:58 by srheede          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ./srcs/*.c

HEADER = libft.h

OBJ = ./*.o


FLAG = -Wall -Werror -Wextra -g

$(NAME):
	gcc $(FLAG) -c $(SRCS) -I $(HEADER)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	@printf "\e[32m[✓] LIBFT COMPILED\n"
	make -C ./ clean

.PHONY: all
all: $(NAME)

.PHONY:	clean
clean:
	@rm -f $(OBJ)
	@printf "\e[31m[✓] LIBFT OBJECT FILES REMOVED\n"

.PHONY:	fclean
fclean: clean
	@rm -f $(NAME)
	@printf "\e[31m[✓] LIBFT LIBRARY REMOVED\n"

.PHONY:	re
re: fclean all

