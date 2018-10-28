# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/14 19:41:42 by amyburgh          #+#    #+#              #
#    Updated: 2018/10/24 18:37:07 by amyburgh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf.a

CC = gcc
CFLAFGS = -Wall -Werror -Wextra
DUBUG = -fsanitize=address

SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./include

LIBFT = ./libft

SRC_FILES = ft_printf.c \
			options.c \
			dispatch.c \
			tools.c \
			\
			fmt_s.c \
#			fmt_ss.c \
			\

SRC = $(addprefix $(SRCDIR)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJDIR)/, $(SRC_FILES:.c=.o))
INC = $(addprefix -I, $(INCDIR))

.PHONY: all clean fclean re
.SILENT:

all: build $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT)
	ar rc $@ $^
	ranlib $@
#	$(CC) $(CFLAGS) -L $(LIBFT) -lft -o $@ $^
	echo "ft_printf.a: \033[32m[CREATED]\033[0m"

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CLFAGS) $(INC) -I $(LIBFT)/include -o $@ -c $<

build:
	mkdir -p $(OBJDIR)

clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJDIR)
	echo "object_files: \033[32[REMOVED]\033[0m"

fclean:	clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)
	echo "ft_printf.a: \033[32m[REMOVED]\033[0m"

re:	fclean all
