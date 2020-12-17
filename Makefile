# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/15 14:29:49 by rsanchez          #+#    #+#              #
#    Updated: 2020/12/17 13:23:00 by rsanchez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CC = clang

FLAGS = -Wall -Wextra -Werror

FLAGSHARD = -Weverything

LIB	= libraries

LIBLINUX = minilibx-linux

HEADER = includes

DIR_S = sources

DIR_PARS = parsing

DIR_O = temporary

SOURCES = main.c \

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIB)/$(LIBLINUX)
	cp $(LIB)/$(LIBLINUX)/libmlx.a .
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) -L. -lmlx -lXext -lX11

$(DIR_O)/%.o: $(DIR_S)/%.c
	mkdir -p $(DIR_O)
	$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

norme:
	@echo
	norminette $(HEADER)/
	@echo
	norminette $(DIR_S)/

soft: $(OBJS)
	make -C $(LIB)/$(LIBLINUX)
	cp $(LIB)/$(LIBLINUX)/libmlx.a .
	$(CC) -o $(NAME) -I $(HEADER) $(OBJS) -L. -lmlx -lXext -lX11

hardmode: $(OBJS)
	make -C $(LIB)/$(LIBLINUX)
	cp $(LIB)/$(LIBLINUX)/libmlx.a .
	$(CC) $(FLAGSHARD) -o $(NAME)_hardmode -I $(HEADER) $(OBJS) -L. -lmlx -lXext -lX11

clean:
	rm -f $(OBJS)
	rm -rf $(DIR_O)
	make clean -C $(LIB)/$(LIBLINUX)

fclean: clean
	rm -f $(NAME)_hardmode
	rm -f $(NAME)
	rm -f libmlx.a

re: fclean all

.PHONY:		all clean fclean re
