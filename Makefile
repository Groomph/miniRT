# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/15 14:29:49 by rsanchez          #+#    #+#              #
#    Updated: 2021/01/20 23:14:31 by rsanchez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CC = clang

CFLAGS = -Wall -Wextra -Werror

FLAGSHARD = -Weverything

LIB	= libraries

LIBFT	= -L $(LIB)/libft/ -lft

LIBLINUX = -L $(LIB)/minilibx-linux/ -lmlx -lXext -lX11 -lm

LIBMAC	= -L $(LIB)/minilibx_opengl_20191021/

HEADER = includes

DIR_S = sources

DIR_PARS = parsing

DIR_LIST = list

DIR_O = temporary

SOURCES = main.c $(DIR_PARS)/file_parsing.c $(DIR_PARS)/parsing_utils.c \
	  vector/vector_operations.c vector/vector_getters.c \
	  ray_caster.c camera.c sphere.c light_color.c quit_program.c 

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIB)/libft
	make -C $(LIB)/minilibx-linux
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIBLINUX)

$(DIR_O)/%.o: $(DIR_S)/%.c
	mkdir -p $(DIR_O)
	mkdir -p $(DIR_O)/vector
	mkdir -p $(DIR_O)/parsing
	mkdir -p $(DIR_O)/libft
	$(CC) -I $(HEADER) -o $@ -c $<

norme:
	@echo
	norminette $(HEADER)/
	@echo
	norminette $(DIR_S)/

hardmode: $(OBJS)
	make -C $(LIB)/libft
	make -C $(LIB)/minilibx-linux
	$(CC) $(FLAGSHARD) -o $(NAME)_hardmode -I $(HEADER) $(OBJS) $(LIBLINUX) $(LIBFT)

soft: $(OBJS)
	make -C $(LIB)/libft
	make -C $(LIB)/minilibx-linux
	$(CC) -o $(NAME) -I $(HEADER) $(OBJS) $(LIBLINUX) $(LIBFT)

clean:
	rm -f $(OBJS)
	rm -rf $(DIR_O)
	make fclean -C $(LIB)/libft
	make clean -C $(LIB)/minilibx-linux

fclean: clean
	rm -f $(NAME)_hardmode
	rm -f $(NAME)
	rm -f libmlx.a

re: fclean all

.PHONY:		all clean fclean re
