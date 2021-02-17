# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/15 14:29:49 by rsanchez          #+#    #+#              #
#    Updated: 2021/02/17 15:30:55 by rsanchez         ###   ########.fr        #
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

DIR_RAYC = ray_caster

DIR_PARS = scene_parsing

DIR_EQUA = equations_objects

DIR_VECM = vector_matrice

DIR_CONT = controls

DIR_O = temporary

SOURCES = main.c save.c \
	  $(DIR_RAYC)/fill_pixel.c $(DIR_RAYC)/path_tracer.c $(DIR_RAYC)/light_shader.c \
	  $(DIR_RAYC)/color_disruption.c \
	  $(DIR_PARS)/file_parsing.c $(DIR_PARS)/parsing_utils.c $(DIR_PARS)/add_object.c \
	  $(DIR_PARS)/camera.c $(DIR_PARS)/light.c $(DIR_PARS)/sphere.c \
	  $(DIR_PARS)/plane.c $(DIR_PARS)/triangle.c $(DIR_PARS)/square.c \
	  $(DIR_PARS)/cylinder.c $(DIR_PARS)/cube.c $(DIR_PARS)/pyramide.c \
	  $(DIR_PARS)/cone.c \
	  $(DIR_EQUA)/sphere.c $(DIR_EQUA)/plane.c $(DIR_EQUA)/triangle.c \
	  $(DIR_EQUA)/square.c $(DIR_EQUA)/cylinder.c $(DIR_EQUA)/disk.c \
	  $(DIR_EQUA)/cone.c \
	  $(DIR_CONT)/lobby.c $(DIR_CONT)/quit_program.c \
	  $(DIR_VECM)/vector_operations.c $(DIR_VECM)/vector_getters.c \
	  $(DIR_VECM)/matrice.c $(DIR_VECM)/color.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIB)/libft
	make -C $(LIB)/minilibx-linux
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIBLINUX)

$(DIR_O)/%.o: $(DIR_S)/%.c
	mkdir -p $(DIR_O)
	mkdir -p $(DIR_O)/$(DIR_RAYC)
	mkdir -p $(DIR_O)/$(DIR_PARS)
	mkdir -p $(DIR_O)/$(DIR_EQUA)
	mkdir -p $(DIR_O)/$(DIR_VECM)
	mkdir -p $(DIR_O)/$(DIR_CONT)
	$(CC) -g -I $(HEADER) -o $@ -c $<

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
