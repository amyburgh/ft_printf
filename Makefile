# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/15 20:13:18 by amyburgh          #+#    #+#              #
#    Updated: 2018/11/30 23:02:18 by amyburgh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra -O3

SRC_FILES = ft_printf \
			formatting \
			tools \
			length

INCDIR = ./libft/include

SRC = $(addsuffix .c, $(SRC_FILES))
OBJ = $(addsuffix .o, $(SRC_FILES))
INC = $(addprefix -I , $(INCDIR))

.PHONY: all clean fclean re
.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	gcc $(CFLAGS) $(INC) -c $(SRC) 
	ar rc $@ $^ libft/obj/*.o
	ranlib $@
	echo $(NAME)": \033[32m[CREATED]\033[0m"

clean:
	make -C libft clean
	rm -f $(OBJ)
	echo "object_files: \033[32m[REMOVED]\033[0m"

fclean:
	make -C libft fclean
	rm -f $(OBJ)
	rm -f $(NAME)
	echo $(NAME)": \033[32m[REMOVED]\033[0m"

re: fclean all
