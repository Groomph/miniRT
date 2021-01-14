# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/15 14:25:42 by rsanchez          #+#    #+#              #
#    Updated: 2021/01/13 18:17:05 by rsanchez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= init_zero.c is_double_signed.c shift_left_erase.c shift_right_add.c \
	  str_n_comp.c string_len.c strjoin_free.c substr_free.c utoa_base.c \
	  utoa_len.c is_infinite.c is_not_number.c get_next_line.c \
	  atodoub_windex.c atoi_windex.c str_nstr_comp.c \
	  list_new.c list_add_front.c list_add_back.c \
	  list_size.c list_last.c list_iter.c \
	  list_map.c list_delone.c list_clear.c

OBJS	= ${SRCS:.c=.o}

BOBJS	= ${BSRCS:.c=.o}

NAME	= libft.a

CC	= clang

CFLAGS	= -Wall -Wextra -Werror

RM	= rm -f

$(NAME):	${OBJS}
			ar rc ${NAME} ${OBJS} libft.h

all:		${NAME}

clean:
		${RM} ${OBJS} ${BOBJS}

fclean:		clean
		${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
