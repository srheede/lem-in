# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srheede <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/26 15:30:46 by srheede           #+#    #+#              #
#    Updated: 2018/08/24 16:52:14 by srheede          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRCS = *.c

OBJ = $(SRCS:.c=.o)

FLAG = -Wall -Werror -Wextra

$(NAME):
	@make -C libft/
	@gcc $(FLAG) $(addprefix srcs/, $(SRCS)) -L ./libft -lft -o $(NAME)
	@printf "\e[32m[✓] LEM-IN COMPILED\n"
	@make -C ./ clean

.PHONY: all
all: $(NAME)

.PHONY:	clean
clean:
	@rm -f $(OBJ)
	@make -C libft/ clean
	@printf "\e[31m[✓] LEM-IN OBJECT FILES REMOVED\n"

.PHONY:	fclean
fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean
	@printf "\e[31m[✓] LEM-IN EXCECUTABLE REMOVED\n"

.PHONY:	re
re: fclean all
