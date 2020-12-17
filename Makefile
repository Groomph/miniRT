# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/15 14:29:49 by rsanchez          #+#    #+#              #
#    Updated: 2020/12/17 15:59:55 by rsanchez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CC = clang

CFLAGS = -Wall -Wextra -Werror

EXTRAFLAGS = -Weverything

LIB	= libraries

LIBLINUX = -L $(LIB)/minilibx-linux/ -lmlx -lXext -lX11

LIBMAC	= -L $(LIB)/minilibx_opengl_20191021/

HEADER = includes

DIR_S = sources

DIR_PARS = parsing

DIR_O = temporary

SOURCES = main.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIB)/minilibx-linux
	cp $(LIB)/minilibx-linux/libmlx.a .
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBLINUX)

$(DIR_O)/%.o: $(DIR_S)/%.c
	$(CFLAGS) = bite	
	mkdir -p $(DIR_O)
	$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<

norme:
	@echo
	norminette $(HEADER)/
	@echo
	norminette $(DIR_S)/

soft: $(OBJS)
	make -C $(LIB)/minilibx-linux
	cp $(LIB)/minilibx-linux/libmlx.a .
	$(CC) -o $(NAME) -I $(HEADER) $(OBJS) $(LIBLINUX)

hardmode: $(OBJS)
	make -C $(LIB)/minilibx-linux
	cp $(LIB)/minilibx-linux/libmlx.a .
	$(CC) $(FLAGSHARD) -o $(NAME)_hardmode -I $(HEADER) $(OBJS) $(LIBLINUX)

clean:
	rm -f $(OBJS)
	rm -rf $(DIR_O)
	make clean -C $(LIB)/minilibx-linux

fclean: clean
	rm -f $(NAME)_hardmode
	rm -f $(NAME)
	rm -f libmlx.a

re: fclean all

.PHONY:		all clean fclean re
